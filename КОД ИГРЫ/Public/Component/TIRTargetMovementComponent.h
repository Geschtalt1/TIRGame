/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                      КОМПОНЕНТ ДВИЖЕНИЯ МИШЕНИ                                                            */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TIRTargetMovementComponent.generated.h"

//#define DebugDirection
//#define DebugZero


DECLARE_DELEGATE_OneParam(FMovementUpdateSignature, float); // Делегат движение мишени

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLAYRIX_API UTIRTargetMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTIRTargetMovementComponent(const FObjectInitializer& ObjectInitializer);

public:
	/* GETTERS */
	/* Возращает владельца компонента */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Movement Owner")
	FORCEINLINE ATIREnemyBase* GetOwnerMovement() const { return OwnerMovement; };

	/* Возращает скорость перемещения */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Movement Speed")
	FORCEINLINE float GetSpeedMovement() const { return SpeedMovement; };

	/* Возращаем вектор направления мишени */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Movement Direction")
	FORCEINLINE FVector2D GetDirectionMovement() const { return Direction; };

public:
	/* SETTERS */
	/* Установить скорость перемещения */
	UFUNCTION(BlueprintCallable, Category = "Movement Speed")
	virtual void SetSpeedMovement(float NewSpeed);

	/* Установить направление перемещения */
	UFUNCTION(BlueprintCallable, Category = "Movement Direction")
	virtual void SetDirectionMovement(FVector2D NewDirection);

	/* Случайное направление */
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
	/* Движение мишени */
	virtual void MischenMovement(float DeltaTime);

private:
	/* VARIEBLE */
	/* Ссылка на владельца компонента */
	UPROPERTY(Transient)
	class ATIREnemyBase* OwnerMovement;

	/* Ссылка на контроллер */
	UPROPERTY(Transient)
	class ATIRPlayerController* PlayerController;

	/* Скорость перемещения */
	UPROPERTY()
	float SpeedMovement;

	/* Вектор направления */
	UPROPERTY()
	FVector2D Direction;

	/* Делегат обновления перемещения мишени */
	FMovementUpdateSignature MovementUpdateDelegate;
		
};
