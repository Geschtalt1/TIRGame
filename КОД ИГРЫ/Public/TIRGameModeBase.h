/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                              GAME MODE                                                                    */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TIRGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PLAYRIX_API ATIRGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	/* ����������� */
	ATIRGameModeBase(const FObjectInitializer& ObjectInitializer);

public:
	/* ��������� ������� ���-�� ������� */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Enemy Count")
	FORCEINLINE int32 GetEnemyCount() const { return EnemyCount; }

	/* ��������� ������ �� ������� ������ */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Widget Game")
	FORCEINLINE UTIRGameWidget* GetGameWidget() const { return GameWidgetRef;}


public:
	/* FUNCTION */
	/* �������� ����� ������� �������� �� ������ */
	virtual void CheckEnemyCount();

	/* ���� ������ ������� */
	virtual void DeadEnemy();

protected:
	/* ���������� ����� ����� ������� ����� �� ������� */
	virtual void PostLogin(APlayerController* NewPlayer) override;

private:
	/* ������ �� ��������� �������� ������� ��������� �� ���������� */
	void Timer();

private:
	/* ���-�� ������� ��� ������ */
	int32 EnemyCount;

	/* ���-�� ���������� ����� */
	int32 Minute;

	/* ���-�� ���������� ������ */
	int32 Second;

	/* ����� �������� ������� ������� ��������� �� ������ */
	TSubclassOf<UUserWidget> GameWidgetClass;

	/* ����� ������� �������� */
	TSubclassOf<UUserWidget> WinWidgetClass;

	/* ����� ������� ��������� */
	TSubclassOf<UUserWidget> LoseWidgetClass;

	/* ������ */
	FTimerHandle TH_Play;

	/* ������ �� ������� ������ */
	UPROPERTY(Transient)
	class UTIRGameWidget* GameWidgetRef;
};
