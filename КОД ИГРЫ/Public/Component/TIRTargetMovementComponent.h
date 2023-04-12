/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                      ��������� �������� ������                                                            */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TIRTargetMovementComponent.generated.h"

//#define DebugDirection
//#define DebugZero


DECLARE_DELEGATE_OneParam(FMovementUpdateSignature, float); // ������� �������� ������

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLAYRIX_API UTIRTargetMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTIRTargetMovementComponent(const FObjectInitializer& ObjectInitializer);

public:
	/* GETTERS */
	/* ��������� ��������� ���������� */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Movement Owner")
	FORCEINLINE ATIREnemyBase* GetOwnerMovement() const { return OwnerMovement; };

	/* ��������� �������� ����������� */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Movement Speed")
	FORCEINLINE float GetSpeedMovement() const { return SpeedMovement; };

	/* ��������� ������ ����������� ������ */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Movement Direction")
	FORCEINLINE FVector2D GetDirectionMovement() const { return Direction; };

public:
	/* SETTERS */
	/* ���������� �������� ����������� */
	UFUNCTION(BlueprintCallable, Category = "Movement Speed")
	virtual void SetSpeedMovement(float NewSpeed);

	/* ���������� ����������� ����������� */
	UFUNCTION(BlueprintCallable, Category = "Movement Direction")
	virtual void SetDirectionMovement(FVector2D NewDirection);

	/* ��������� ����������� */
	UFUNCTION(BlueprintCallable, Category = "Movement Direction")
	virtual void RandomDirection(FVector2D& V);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	/* FUNCTION */
	/* �������� ������ */
	virtual void MischenMovement(float DeltaTime);

private:
	/* VARIEBLE */
	/* ������ �� ��������� ���������� */
	UPROPERTY(Transient)
	class ATIREnemyBase* OwnerMovement;

	/* ������ �� ���������� */
	UPROPERTY(Transient)
	class ATIRPlayerController* PlayerController;

	/* �������� ����������� */
	UPROPERTY()
	float SpeedMovement;

	/* ������ ����������� */
	UPROPERTY()
	FVector2D Direction;

	/* ������� ���������� ����������� ������ */
	FMovementUpdateSignature MovementUpdateDelegate;
		
};
