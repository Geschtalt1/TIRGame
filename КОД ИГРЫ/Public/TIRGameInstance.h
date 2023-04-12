/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                              GAME INSTANCE                                                                */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TIRGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PLAYRIX_API UTIRGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	/* Конструктор */
	UTIRGameInstance(const FObjectInitializer& ObjectInitializer);

public:
	/* GETTERS */
	/* Возращает кол-во создаваемых мишеней */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Setting Game")
	FORCEINLINE int32 GetEnemyCountSpawn() const { return EnemyCountSpawn; }

	/* Возращает время за который нужно пройти уровень */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Setting Game")
	FORCEINLINE int32 GetTimeMinute() const { return TimeMinute; }

public:
	/* SETTERS */
	/* Установить кол-во врагов */
	UFUNCTION(BlueprintCallable, Category = "Setting Game")
	virtual void SetEnemyCountSpawn(int32 CountSpawn);

	/* Установить время игры */
	UFUNCTION(BlueprintCallable, Category = "Setting Game")
	virtual void SetTimeGame(int32 NewMinute);

private:
	/* Передает в гейм мод нужное кол-во мишений для спавна */
	UPROPERTY()
	int32 EnemyCountSpawn;

	/* Передает в гейм мод кол-во минут */
	UPROPERTY()
	int32 TimeMinute;

};