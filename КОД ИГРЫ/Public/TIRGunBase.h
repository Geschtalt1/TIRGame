// Fill out your copyright notice in the Description page of Project Settings.
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                              ОРУЖИЕ                                                                       */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TIRGunBase.generated.h"

DECLARE_DELEGATE(FRotationUpdateSignature); // Делегат обновления вращения

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

	/* Компонент изображение оружия */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UPaperSpriteComponent* SpriteGun;

	/* Компонент изображение вспышки */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UPaperSpriteComponent* SpriteMuzzle;

public:
	/* GETTERS */
	/* Возращает компонент спрайта оружия */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Gun Component")
	FORCEINLINE UPaperSpriteComponent* GetSpriteGunComponent() const { return SpriteGun; };

	/* Возращает ноносимый урон пушкой */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Gun Dammage")
	FORCEINLINE float GetDammage() const { return Dammage; };

	/* Возращает скорострельность огня */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Gun Dammage")
	FORCEINLINE float GetFireRate() const { return FireRate; };

	/* Возращает звук выстрела */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Gun Dammage")
	FORCEINLINE USoundBase* GetSoudFire() const { return FireSound; };

protected:
	/* SETTERS */
	/* Установить наносимый урон пушки */
	UFUNCTION(BlueprintCallable, Category = "Gun Dammage")
	virtual void SetDammage(float NewDammage);

	/* Установить скорострельность пушки */
	UFUNCTION(BlueprintCallable, Category = "Gun FireRate")
	virtual void SetFireRate(float NewFireRate);

	/* Установить звук стрельбы */
	UFUNCTION(BlueprintCallable, Category = "Gun Sound")
	virtual void SetSoudFire(class USoundBase* NewSound);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Эффект выстрела */
	//UFUNCTION(BlueprintImplementableEvent)
	void EffectMuzzle();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* Стрельба из пушки */
	virtual void OnFire();

private:
	/* FUNCTION */
	/* Вращение оружия */
	UFUNCTION()
	virtual void RotationUpdate();

	/* Показть или скрыть эффект вспышки */
	UFUNCTION()
	virtual void SetMuzzleVisible(bool bVisible);

private:
	/* Обновление вращения оружия */
	FRotationUpdateSignature RotationUpdateDelegat;

	/* Наносимый урон пушки */
	UPROPERTY()
	float Dammage;

	/* Скорострельность */
	UPROPERTY()
	float FireRate;

	/* Звук стрельбы */
	UPROPERTY()
	class USoundBase* FireSound;

};
