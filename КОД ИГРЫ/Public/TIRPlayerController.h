/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                      ���������� ������                                                                    */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TIRPlayerController.generated.h"

UCLASS()
class PLAYRIX_API ATIRPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	/* ����������� */
	ATIRPlayerController(const FObjectInitializer& ObjectInitializer);

public:
	/* GETTERS */
	/* ��������� ������ �� ����� */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerController Weapon")
	FORCEINLINE ATIRGunBase* GetWeapon() const { return GunReference; };

	/* SETTERS */
	/* ���������� ������ �� ����� */
	UFUNCTION(BlueprintCallable, Category = "PlayerController Weapon")
	virtual void SetWeapon(class ATIRGunBase* NewWeapon);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	/* FUNCTION */
	/* ���������� */
	virtual void SetupInputComponent();

	/* ���������� �������� */
	virtual void StopShoot();

protected:
	/* �������� �� ����� */
	virtual void OnFiring();
	virtual void CallShoot();

	/* ����� */
	virtual void CallPause();

public:
	// ��������� ������� ���� �� ����� ��� ���
	bool bPauseEnable;

private:
	/* VARIABLE */
	/* ������ ����� */
	UPROPERTY()
	TSubclassOf<UUserWidget> WidgetPause;

	/* ������ �� ������ */
	UPROPERTY(Transient)
	class UUserWidget* WidgetReference;

	/* ������ �� ����� */
	UPROPERTY(Transient)
	class ATIRGunBase* GunReference;

	/* ������ ������������� �������� */
	UPROPERTY()
	FTimerHandle TH_AutoFiring;
};
