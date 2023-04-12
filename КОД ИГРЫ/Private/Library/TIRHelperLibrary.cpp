/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                         БИБЛИОТЕКА ФУНКЦИЙ                                                                */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


#include "Library/TIRHelperLibrary.h"
#include "TIRGameInstance.h"
#include "TIRPlayerController.h"
#include "Pawns/TIREnemyBase.h"
#include "Pawns/TIREnemyType01.h"
#include "Pawns/TIREnemyType02.h"
#include "Pawns/TIREnemyType03.h"
#include "Pawns/TIREnemyType04.h"

#include "Blueprint/UserWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

/* Установить виджет */
UUserWidget* UTIRHelperLibrary::SetWidgetGame(APlayerController* PlayerController, TSubclassOf<UUserWidget> WidgetCreate, UUserWidget* WidgetRemove)
{
	if (IsValid(WidgetRemove)) // Если удаляемый виджет действителен
		WidgetRemove->RemoveFromParent(); // Удаляем виджет с экрана

	if (IsValid(PlayerController) && IsValid(WidgetCreate)) // Если контроллер и класс виджета выбраны
	{
		UUserWidget* WidgetLocal = CreateWidget<UUserWidget>(PlayerController, WidgetCreate); // Создаем виджет

		if (WidgetLocal) // Проверяем что виджет создан
		{
			WidgetLocal->AddToViewport(); // Выводим на экран
			return WidgetLocal; // Возращаем ссылку на виджет
		}
	}
	return nullptr;
}

/* Спавн врагов */
void UTIRHelperLibrary::SpawnEnemy(const int32 CountEnemy, int32& SuccessfulSpawn)
{
	// Ссылка на мир
	UWorld* World = GEngine->GameViewport->GetWorld();

	if (World)
	{
		// Массив всех типов мишений
		TArray<TSubclassOf<ATIREnemyBase>> AllClassEnemy;

		AllClassEnemy.Add(ATIREnemyType01::StaticClass());
		AllClassEnemy.Add(ATIREnemyType02::StaticClass());
		AllClassEnemy.Add(ATIREnemyType03::StaticClass());
		AllClassEnemy.Add(ATIREnemyType04::StaticClass());

		for (int32 i = 0; i < CountEnemy; i++)
		{
			// Случайная точка, где появиться мишень
			const float SpawnX = UKismetMathLibrary::RandomFloatInRange(-500.0f, 500.0f);
			const float SpawnY = UKismetMathLibrary::RandomFloatInRange(-500.0f, 500.0f);

			FTransform SpawnTransform = FTransform(FRotator(), FVector(SpawnX, -100.0f, SpawnY));

			// Спавн случайной мишени
			int32 RandomMischen = UKismetMathLibrary::RandomIntegerInRange(0, 3);
			ATIREnemyBase* Mischen = World->SpawnActor<ATIREnemyBase>(AllClassEnemy[RandomMischen], SpawnTransform);

			// Возращаем кол-во успешно заспавленных мишений
			if (Mischen)
				SuccessfulSpawn++;
		}
	}
}

/* Настройка игры (установить время и кол-во врагов) */
void UTIRHelperLibrary::SetGameSetting(UGameInstance* GameInstance, int32 Minute, int32 Enemy)
{
	if (IsValid(GameInstance)) // Если гейм инстанс выбран
	{
		UTIRGameInstance* GameInstanceLoc = Cast<UTIRGameInstance>(GameInstance); // Ссылка на инстанс

		if (IsValid(GameInstanceLoc))
		{
			GameInstanceLoc->SetTimeGame(Minute); // Установить время игры
			GameInstanceLoc->SetEnemyCountSpawn(Enemy); // Установить кол-во создаваемых мишеней
		}
	}
}

/* Разрешить ставить паузу в игре или нет */
bool UTIRHelperLibrary::SetPausedWidget(APlayerController* PlayerController, bool bEnable)
{
	ATIRPlayerController* Conroller = Cast<ATIRPlayerController>(PlayerController);
	
	if (IsValid(Conroller))
	{
		Conroller->bPauseEnable = bEnable;

		return bEnable;
	}

	return false;
}