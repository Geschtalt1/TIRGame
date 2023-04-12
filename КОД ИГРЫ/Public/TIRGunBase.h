// Fill out your copyright notice in the Description page of Project Settings.
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                              ������                                                                       */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TIRGunBase.generated.h"

DECLARE_DELEGATE(FRotationUpdateSignature); // ������� ���������� ��������

UCLASS()
class PLAYRIX_API ATIRGunBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATIRGunBase(const FObjectInitializer& ObjectInitializer);

public:
	/* Default Scene Root */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class USceneComponent* DefaultScene;

	/* ��������� ����������� ������ */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UPaperSpriteComponent* SpriteGun;

	/* ��������� ����������� ������� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UPaperSpriteComponent* SpriteMuzzle;

public:
	/* GETTERS */
	/* ��������� ��������� ������� ������ */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Gun Component")
	FORCEINLINE UPaperSpriteComponent* GetSpriteGunComponent() const { return SpriteGun; };

	/* ��������� ��������� ���� ������ */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Gun Dammage")
	FORCEINLINE float GetDammage() const { return Dammage; };

	/* ��������� ���������������� ���� */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Gun Dammage")
	FORCEINLINE float GetFireRate() const { return FireRate; };

	/* ��������� ���� �������� */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Gun Dammage")
	FORCEINLINE USoundBase* GetSoudFire() const { return FireSound; };

protected:
	/* SETTERS */
	/* ���������� ��������� ���� ����� */
	UFUNCTION(BlueprintCallable, Category = "Gun Dammage")
	virtual void SetDammage(float NewDammage);

	/* ���������� ���������������� ����� */
	UFUNCTION(BlueprintCallable, Category = "Gun FireRate")
	virtual void SetFireRate(float NewFireRate);

	/* ���������� ���� �������� */
	UFUNCTION(BlueprintCallable, Category = "Gun Sound")
	virtual void SetSoudFire(class USoundBase* NewSound);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* ������ �������� */
	//UFUNCTION(BlueprintImplementableEvent)
	void EffectMuzzle();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* �������� �� ����� */
	virtual void OnFire();

private:
	/* FUNCTION */
	/* �������� ������ */
	UFUNCTION()
	virtual void RotationUpdate();

	/* ������� ��� ������ ������ ������� */
	UFUNCTION()
	virtual void SetMuzzleVisible(bool bVisible);

private:
	/* ���������� �������� ������ */
	FRotationUpdateSignature RotationUpdateDelegat;

	/* ��������� ���� ����� */
	UPROPERTY()
	float Dammage;

	/* ���������������� */
	UPROPERTY()
	float FireRate;

	/* ���� �������� */
	UPROPERTY()
	class USoundBase* FireSound;

};
