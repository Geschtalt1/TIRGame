/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                              ����                                                                         */
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
	/* ��������� �������� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class USphereComponent* SphereBullet;

	/* ��������� ����������� ���� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UPaperSpriteComponent* SpriteProjectile;

public:
	/* GETTERS */
	/* ��������� ���� ���� */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Bullet Dammage")
	FORCEINLINE float GetBulletDammage() const { return BulletDammage; };

	/* ��������� �������� ���� */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Bullet Speed")
	FORCEINLINE float GetBulletSpeed() const { return BulletSpeed; };

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* SETTERS */
	/* ���������� ���� ���� */
	void SetBulletDammage(float NewDammage);

	/* ���������� �������� ���� */
	void SetBulletSpeed(float NewSpeed);

	/* ��������� � ������ */
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, 
		class AActor* OtherActor, 
		class UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult);

private:
	/* VARIEBLE */
	/* ���� ���� �� ������� */
	UPROPERTY()
	float BulletDammage;

	/* �������� ���� */
	UPROPERTY()
	float BulletSpeed;

};
