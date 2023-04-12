/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                      КОНТРОЛЛЕР ИГРОКА                                                                    */
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
	/* Конструктор */
	ATIRPlayerController(const FObjectInitializer& ObjectInitializer);

public:
	/* GETTERS */
	/* Возращаем ссылку на пушку */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerController Weapon")
	FORCEINLINE ATIRGunBase* GetWeapon() const { return GunReference; };

	/* SETTERS */
	/* Установить ссылку на пушку */
	UFUNCTION(BlueprintCallable, Category = "PlayerController Weapon")
	virtual void SetWeapon(class ATIRGunBase* NewWeapon);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	/* FUNCTION */
	/* Управление */
	virtual void SetupInputComponent();

	/* Остановить стрельбу */
	virtual void StopShoot();

protected:
	/* Стрельба из пушки */
	virtual void OnFiring();
	virtual void CallShoot();

	/* Пауза */
	virtual void CallPause();

public:
	// Разрешает ставить игру на паузу или нет
	bool bPauseEnable;

private:
	/* VARIABLE */
	/* Виджет паузы */
	UPROPERTY()
	TSubclassOf<UUserWidget> WidgetPause;

	/* Ссылка на виджет */
	UPROPERTY(Transient)
	class UUserWidget* WidgetReference;

	/* Ссылка на пушку */
	UPROPERTY(Transient)
	class ATIRGunBase* GunReference;

	/* Таймер атоматической стрельбы */
	UPROPERTY()
	FTimerHandle TH_AutoFiring;
};
