/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                              ������                                                                       */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "TIREnemyBase.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(FDeadEnemySignature); // ������� ������ ������

UCLASS()
class PLAYRIX_API ATIREnemyBase : public AActor
{
	GENERATED_BODY()
	
public:
	/* ����������� */
	ATIREnemyBase(const FObjectInitializer& ObjectInitializer);

	/* ��������� �������� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class USphereComponent* Sphere;

	/* ��������� ����������� ������ */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UPaperSpriteComponent* SpriteEnemy;

	/* ��������� ����������� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UTIRTargetMovementComponent* MovementComponent;

	/* ��������� ������� �������� ������ */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UWidgetComponent* HealthWidgetComponent;

public:
	/* GETTERS */
	/* ��������� ��������� ������� ������ */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Enemy Component")
	FORCEINLINE UPaperSpriteComponent* GetSpriteEnemyComponent() const { return SpriteEnemy; };

	/* ��������� ��������� �������� */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Enemy Component")
	FORCEINLINE UTIRTargetMovementComponent* GetMovementComponent() const { return MovementComponent; };

	/* ��������� ������� ���-�� �������� ������ */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Enemy Health")
	FORCEINLINE float GetHealthCurrent() const { return HealthCurrent; };

	/* ��������� ������������ ���-�� �������� ������ */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Enemy Health")
	FORCEINLINE float GetHealthMax() const { return HealthMax; };

public:
	/* SETTERS */
	/* ���������� ������� ���-�� �������� ������ */
	UFUNCTION(BlueprintCallable, Category = "Enemy Health")
	virtual float SetHealthCurrent(const float NewHealth);

	/* ���������� ������������ ���-�� �������� ������ */
	UFUNCTION(BlueprintCallable, Category = "Enemy Health")
	virtual void SetHealthMax(const float NewHealthMax);

	/* ���������� ������ ������ */
	UFUNCTION(BlueprintCallable, Category = "Enemy Health")
	virtual void SetSizeEnemy(const float NewSize);

	/* ���������� ���� ������ */
	UFUNCTION(BlueprintCallable, Category = "Enemy Color")
	virtual void SetColorEnemy(FLinearColor NewColor);

public:
	/* ��������� ����� */
	virtual float TakeDamage(float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser) override;

	/* ������������ ������� ���� �� �����  */
	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		FVector NormalImpulse,
		const FHitResult& Hit);

protected:
	/* ������ ���� */
	virtual void BeginPlay() override;

private:
	/* VARIEBLE */
	/* ������� ���-�� �� */
	UPROPERTY()
	float HealthCurrent;

	/* ������������ ���-�� �� */
	UPROPERTY()
	float HealthMax;

	// ������ �� ������ ��������
	UPROPERTY()
	class UTIRHealthWidget* HealthWidget;

private:
	/* FUNCTION */
	/* ������ ������ */
	void Dead();
};