/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                              ПУЛЯ                                                                         */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TIRProjectile.generated.h"

UCLASS()
class PLAYRIX_API ATIRProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATIRProjectile();

public:
	/* Компонент коллизии */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class USphereComponent* SphereBullet;

	/* Компонент изображение пули */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UPaperSpriteComponent* SpriteProjectile;

public:
	/* GETTERS */
	/* Возращает урон пули */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Bullet Dammage")
	FORCEINLINE float GetBulletDammage() const { return BulletDammage; };

	/* Возращает скорость пули */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Bullet Speed")
	FORCEINLINE float GetBulletSpeed() const { return BulletSpeed; };

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* SETTERS */
	/* Установить урон пули */
	void SetBulletDammage(float NewDammage);

	/* Установить скорость пули */
	void SetBulletSpeed(float NewSpeed);

	/* Попадание в мишень */
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, 
		class AActor* OtherActor, 
		class UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult);

private:
	/* VARIEBLE */
	/* Урон пули по мишеням */
	UPROPERTY()
	float BulletDammage;

	/* Скорость пули */
	UPROPERTY()
	float BulletSpeed;

};
