/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                              GAME MODE                                                                    */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#include "TIRGameModeBase.h"
#include "TIRGameInstance.h"
#include "Pawns/TIREnemyBase.h"
#include "Pawns/TIREnemyType01.h"
#include "Pawns/TIREnemyType02.h"
#include "Pawns/TIREnemyType03.h"
#include "Pawns/TIREnemyType04.h"
#include "TIRPlayerController.h"
#include "Widget/TIRGameWidget.h"
#include "Library/TIRHelperLibrary.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/GameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ATIRGameModeBase::ATIRGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	Minute = 0;
	Second = 60;
	EnemyCount = 0;

	WinWidgetClass = nullptr;
	LoseWidgetClass = nullptr;
	GameWidgetClass = nullptr;

	static ConstructorHelpers::FClassFinder<UUserWidget> WB_GameplayAsset(TEXT
	("/Game/Playerix/Widget/WB_Gameplay"));

	static ConstructorHelpers::FClassFinder<UUserWidget> WB_WinAsset(TEXT
	("/Game/Playerix/Widget/WB_Win"));

	static ConstructorHelpers::FClassFinder<UUserWidget> WB_LoseAsset(TEXT
	("/Game/Playerix/Widget/WB_Lose"));

	if (WB_GameplayAsset.Succeeded())
		GameWidgetClass = WB_GameplayAsset.Class;

	if (WB_WinAsset.Succeeded())
		WinWidgetClass = WB_WinAsset.Class;

	if (WB_LoseAsset.Succeeded())
		LoseWidgetClass = WB_LoseAsset.Class;


}

/* Вызывается когда игрок успешно зашел на уровень */
void ATIRGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	UTIRGameInstance* GameInstanceLoc = Cast<UTIRGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (IsValid(GameInstanceLoc))
	{
		const int32 CountSpawn = GameInstanceLoc->GetEnemyCountSpawn(); // Сколько нужно заспавнить
		Minute = GameInstanceLoc->GetTimeMinute(); // Время за которое нужно успеть пройти уровень

		UTIRHelperLibrary::SpawnEnemy(CountSpawn, EnemyCount); // Спавним мишени
		UUserWidget* WidgetLocal = UTIRHelperLibrary::SetWidgetGame(NewPlayer, 
			GameWidgetClass, nullptr); // Спавн игрового виджета

		if (WidgetLocal) // Если виджет создался
			GameWidgetRef = Cast<UTIRGameWidget>(WidgetLocal); // Каст на игровой виджет

		if (GetGameWidget()) // Проверяем что ссылка на игровой виджет есть
		{
			GetGameWidget()->SetCountEnemy(EnemyCount); // Устанавливаем начальное кол-во оставшихся мишеней в виджет
			GetGameWidget()->SetCountMinut(Minute); // Устанавливаем начальное кол-во минут в виджет
			GetGameWidget()->SetCountSecond(Second); // Устанавливаем начальное кол-во секунд в виджет
		}

		GetWorldTimerManager().SetTimer(TH_Play, this, &ATIRGameModeBase::Timer, 1.0f, true, 0.0f); // Запускаем отсчет времени

	}
	
	CheckEnemyCount(); // Проверяем предварительно что мишени заспавнились
}

/* Проверяем условие победы */
void ATIRGameModeBase::CheckEnemyCount()
{
	if (GetEnemyCount() <= 0) // Если мишений меньше или равно нулю
	{
		GetWorldTimerManager().PauseTimer(TH_Play); // Останавиваем таймер
		GetWorldTimerManager().ClearTimer(TH_Play); // Очищаем таймер

		UGameplayStatics::SetGamePaused(this, true); // Включаем паузу

		if (IsValid(WinWidgetClass))  // Проверям что класс виджета победы валиден
		{
			APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

			UTIRHelperLibrary::SetPausedWidget(Controller, false); // Запрещаем ставить паузу виджете
			UTIRHelperLibrary::SetWidgetGame(Controller,
				WinWidgetClass, GetGameWidget()); // Спавним в случаи выигрыша виджет победы и удаляем игровой виджет
		}
		else // Если вдруг ссылки на виджет нету
			UGameplayStatics::OpenLevel(this, FName("Level_00")); // Возращаем игрока в меню игры
	}
}

/* Если мишень погибла */
void ATIRGameModeBase::DeadEnemy()
{
	EnemyCount -= 1; // Высчитываем новое кол-во мишеней для победы

	if (GetGameWidget()) // Проверяем что виджет валиден
		GetGameWidget()->SetCountEnemy(EnemyCount); // Устанавливаем кол-во оставшихся мишеней

	CheckEnemyCount(); // Проверяем условия для победы
}

/* Таймер */
void ATIRGameModeBase::Timer()
{
	if (Second != 0) // Обновляем секунды, пока не достигнем нуля
	{
		Second -= 1;
		if (GetGameWidget())
			GetGameWidget()->SetCountSecond(Second); // Обновляем в виджете время в секундах
	}
	else if (Minute != 0) // Как достигли нуля, проверяем была ли эта минута последний
	{
		Minute -= 1;
		Second = 59;

		if (GetGameWidget())
		{
			GetGameWidget()->SetCountMinut(Minute); // Обновляем в виджете время в минутах
			GetGameWidget()->SetCountSecond(Second); // Обновляем в виджете время в секундах 
		}
	}
	else // Если минута была послений, заканчиваем игру
	{
		UTIRHelperLibrary::SetPausedWidget(UGameplayStatics::GetPlayerController(GetWorld(),
			0), false); // Запрещаем ставить паузу виджете

		GetWorldTimerManager().PauseTimer(TH_Play); // Останавиваем таймер
		GetWorldTimerManager().ClearTimer(TH_Play); // Очищаем таймер

		UGameplayStatics::SetGamePaused(this, true); // Включаем паузу

		if (LoseWidgetClass)
			UTIRHelperLibrary::SetWidgetGame(UGameplayStatics::GetPlayerController(GetWorld(), 0),
				LoseWidgetClass, GetGameWidget()); // Спавним виджет поражения и удаляем игровой виджет
	}

}