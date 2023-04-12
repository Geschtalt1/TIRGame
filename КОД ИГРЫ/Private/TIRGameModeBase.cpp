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

/* ���������� ����� ����� ������� ����� �� ������� */
void ATIRGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	UTIRGameInstance* GameInstanceLoc = Cast<UTIRGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (IsValid(GameInstanceLoc))
	{
		const int32 CountSpawn = GameInstanceLoc->GetEnemyCountSpawn(); // ������� ����� ����������
		Minute = GameInstanceLoc->GetTimeMinute(); // ����� �� ������� ����� ������ ������ �������

		UTIRHelperLibrary::SpawnEnemy(CountSpawn, EnemyCount); // ������� ������
		UUserWidget* WidgetLocal = UTIRHelperLibrary::SetWidgetGame(NewPlayer, 
			GameWidgetClass, nullptr); // ����� �������� �������

		if (WidgetLocal) // ���� ������ ��������
			GameWidgetRef = Cast<UTIRGameWidget>(WidgetLocal); // ���� �� ������� ������

		if (GetGameWidget()) // ��������� ��� ������ �� ������� ������ ����
		{
			GetGameWidget()->SetCountEnemy(EnemyCount); // ������������� ��������� ���-�� ���������� ������� � ������
			GetGameWidget()->SetCountMinut(Minute); // ������������� ��������� ���-�� ����� � ������
			GetGameWidget()->SetCountSecond(Second); // ������������� ��������� ���-�� ������ � ������
		}

		GetWorldTimerManager().SetTimer(TH_Play, this, &ATIRGameModeBase::Timer, 1.0f, true, 0.0f); // ��������� ������ �������

	}
	
	CheckEnemyCount(); // ��������� �������������� ��� ������ ������������
}

/* ��������� ������� ������ */
void ATIRGameModeBase::CheckEnemyCount()
{
	if (GetEnemyCount() <= 0) // ���� ������� ������ ��� ����� ����
	{
		GetWorldTimerManager().PauseTimer(TH_Play); // ������������ ������
		GetWorldTimerManager().ClearTimer(TH_Play); // ������� ������

		UGameplayStatics::SetGamePaused(this, true); // �������� �����

		if (IsValid(WinWidgetClass))  // �������� ��� ����� ������� ������ �������
		{
			APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

			UTIRHelperLibrary::SetPausedWidget(Controller, false); // ��������� ������� ����� �������
			UTIRHelperLibrary::SetWidgetGame(Controller,
				WinWidgetClass, GetGameWidget()); // ������� � ������ �������� ������ ������ � ������� ������� ������
		}
		else // ���� ����� ������ �� ������ ����
			UGameplayStatics::OpenLevel(this, FName("Level_00")); // ��������� ������ � ���� ����
	}
}

/* ���� ������ ������� */
void ATIRGameModeBase::DeadEnemy()
{
	EnemyCount -= 1; // ����������� ����� ���-�� ������� ��� ������

	if (GetGameWidget()) // ��������� ��� ������ �������
		GetGameWidget()->SetCountEnemy(EnemyCount); // ������������� ���-�� ���������� �������

	CheckEnemyCount(); // ��������� ������� ��� ������
}

/* ������ */
void ATIRGameModeBase::Timer()
{
	if (Second != 0) // ��������� �������, ���� �� ��������� ����
	{
		Second -= 1;
		if (GetGameWidget())
			GetGameWidget()->SetCountSecond(Second); // ��������� � ������� ����� � ��������
	}
	else if (Minute != 0) // ��� �������� ����, ��������� ���� �� ��� ������ ���������
	{
		Minute -= 1;
		Second = 59;

		if (GetGameWidget())
		{
			GetGameWidget()->SetCountMinut(Minute); // ��������� � ������� ����� � �������
			GetGameWidget()->SetCountSecond(Second); // ��������� � ������� ����� � �������� 
		}
	}
	else // ���� ������ ���� ��������, ����������� ����
	{
		UTIRHelperLibrary::SetPausedWidget(UGameplayStatics::GetPlayerController(GetWorld(),
			0), false); // ��������� ������� ����� �������

		GetWorldTimerManager().PauseTimer(TH_Play); // ������������ ������
		GetWorldTimerManager().ClearTimer(TH_Play); // ������� ������

		UGameplayStatics::SetGamePaused(this, true); // �������� �����

		if (LoseWidgetClass)
			UTIRHelperLibrary::SetWidgetGame(UGameplayStatics::GetPlayerController(GetWorld(), 0),
				LoseWidgetClass, GetGameWidget()); // ������� ������ ��������� � ������� ������� ������
	}

}