/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                              МИШЕНИ                                                                       */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "TIREnemyBase.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(FDeadEnemySignature); // Делегат смерти мишени

UCLASS()
class PLAYRIX_API ATIREnemyBase : public AActor
{
	GENERATED_BODY()
	
public:
	/* Конструктор */
	ATIREnemyBase(const FObjectInitializer& ObjectInitializer);

	/* Компонент коллизии */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class USphereComponent* Sphere;

	/* Компонент изображение мишени */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UPaperSpriteComponent* SpriteEnemy;

	/* Компонент перемещение */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UTIRTargetMovementComponent* MovementComponent;

	/* Компонент виджета здоровья мишени */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UWidgetComponent* HealthWidgetComponent;

public:
	/* GETTERS */
	/* Возращает компонент спрайта мишени */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Enemy Component")
	FORCEINLINE UPaperSpriteComponent* GetSpriteEnemyComponent() const { return SpriteEnemy; };

	/* Возращает компонент движения */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Enemy Component")
	FORCEINLINE UTIRTargetMovementComponent* GetMovementComponent() const { return MovementComponent; };

	/* Возращает текущее кол-во здоровье мишени */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Enemy Health")
	FORCEINLINE float GetHealthCurrent() const { return HealthCurrent; };

	/* Возращает максимальное кол-во здоровье мишени */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Enemy Health")
	FORCEINLINE float GetHealthMax() const { return HealthMax; };

public:
	/* SETTERS */
	/* Установить текущее кол-во здоровье мишени */
	UFUNCTION(BlueprintCallable, Category = "Enemy Health")
	virtual float SetHealthCurrent(const float NewHealth);

	/* Установить максимальное кол-во здоровье мишени */
	UFUNCTION(BlueprintCallable, Category = "Enemy Health")
	virtual void SetHealthMax(const float NewHealthMax);

	/* Установить размер мишени */
	UFUNCTION(BlueprintCallable, Category = "Enemy Health")
	virtual void SetSizeEnemy(const float NewSize);

	/* Установить цвет мишени */
	UFUNCTION(BlueprintCallable, Category = "Enemy Color")
	virtual void SetColorEnemy(FLinearColor NewColor);

public:
	/* Получение урона */
	virtual float TakeDamage(float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser) override;

	/* Столкновения мишений друг об друга  */
	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		FVector NormalImpulse,
		const FHitResult& Hit);

protected:
	/* Начало игры */
	virtual void BeginPlay() override;

private:
	/* VARIEBLE */
	/* Текущее кол-во ХП */
	UPROPERTY()
	float HealthCurrent;

	/* Максимальное кол-во ХП */
	UPROPERTY()
	float HealthMax;

	// Ссылка на виджет здоровья
	UPROPERTY()
	class UTIRHealthWidget* HealthWidget;

private:
	/* FUNCTION */
	/* Смерть мишени */
	void Dead();
};