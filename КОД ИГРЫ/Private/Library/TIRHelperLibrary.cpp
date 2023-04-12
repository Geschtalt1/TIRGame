/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                         ���������� �������                                                                */
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

/* ���������� ������ */
UUserWidget* UTIRHelperLibrary::SetWidgetGame(APlayerController* PlayerController, TSubclassOf<UUserWidget> WidgetCreate, UUserWidget* WidgetRemove)
{
	if (IsValid(WidgetRemove)) // ���� ��������� ������ ������������
		WidgetRemove->RemoveFromParent(); // ������� ������ � ������

	if (IsValid(PlayerController) && IsValid(WidgetCreate)) // ���� ���������� � ����� ������� �������
	{
		UUserWidget* WidgetLocal = CreateWidget<UUserWidget>(PlayerController, WidgetCreate); // ������� ������

		if (WidgetLocal) // ��������� ��� ������ ������
		{
			WidgetLocal->AddToViewport(); // ������� �� �����
			return WidgetLocal; // ��������� ������ �� ������
		}
	}
	return nullptr;
}

/* ����� ������ */
void UTIRHelperLibrary::SpawnEnemy(const int32 CountEnemy, int32& SuccessfulSpawn)
{
	// ������ �� ���
	UWorld* World = GEngine->GameViewport->GetWorld();

	if (World)
	{
		// ������ ���� ����� �������
		TArray<TSubclassOf<ATIREnemyBase>> AllClassEnemy;

		AllClassEnemy.Add(ATIREnemyType01::StaticClass());
		AllClassEnemy.Add(ATIREnemyType02::StaticClass());
		AllClassEnemy.Add(ATIREnemyType03::StaticClass());
		AllClassEnemy.Add(ATIREnemyType04::StaticClass());

		for (int32 i = 0; i < CountEnemy; i++)
		{
			// ��������� �����, ��� ��������� ������
			const float SpawnX = UKismetMathLibrary::RandomFloatInRange(-500.0f, 500.0f);
			const float SpawnY = UKismetMathLibrary::RandomFloatInRange(-500.0f, 500.0f);

			FTransform SpawnTransform = FTransform(FRotator(), FVector(SpawnX, -100.0f, SpawnY));

			// ����� ��������� ������
			int32 RandomMischen = UKismetMathLibrary::RandomIntegerInRange(0, 3);
			ATIREnemyBase* Mischen = World->SpawnActor<ATIREnemyBase>(AllClassEnemy[RandomMischen], SpawnTransform);

			// ��������� ���-�� ������� ������������ �������
			if (Mischen)
				SuccessfulSpawn++;
		}
	}
}

/* ��������� ���� (���������� ����� � ���-�� ������) */
void UTIRHelperLibrary::SetGameSetting(UGameInstance* GameInstance, int32 Minute, int32 Enemy)
{
	if (IsValid(GameInstance)) // ���� ���� ������� ������
	{
		UTIRGameInstance* GameInstanceLoc = Cast<UTIRGameInstance>(GameInstance); // ������ �� �������

		if (IsValid(GameInstanceLoc))
		{
			GameInstanceLoc->SetTimeGame(Minute); // ���������� ����� ����
			GameInstanceLoc->SetEnemyCountSpawn(Enemy); // ���������� ���-�� ����������� �������
		}
	}
}

/* ��������� ������� ����� � ���� ��� ��� */
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