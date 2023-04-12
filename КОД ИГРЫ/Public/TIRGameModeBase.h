/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                              GAME MODE                                                                    */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TIRGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PLAYRIX_API ATIRGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	/* Конструктор */
	ATIRGameModeBase(const FObjectInitializer& ObjectInitializer);

public:
	/* Возращает текущее кол-во мишеней */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Enemy Count")
	FORCEINLINE int32 GetEnemyCount() const { return EnemyCount; }

	/* Возращает ссылку на игровой виджет */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Widget Game")
	FORCEINLINE UTIRGameWidget* GetGameWidget() const { return GameWidgetRef;}


public:
	/* FUNCTION */
	/* Проверка скока мишений осталось до победы */
	virtual void CheckEnemyCount();

	/* Если мишень погибла */
	virtual void DeadEnemy();

protected:
	/* Вызывается когда игрок успешно зашел на уровень */
	virtual void PostLogin(APlayerController* NewPlayer) override;

private:
	/* Таймер по истичению которого уровень считается не пройденным */
	void Timer();

private:
	/* Кол-во мишений для победы */
	int32 EnemyCount;

	/* Кол-во оставшихся минут */
	int32 Minute;

	/* Кол-во оставшихся секунд */
	int32 Second;

	/* Класс игрового виджета который появиться на уровне */
	TSubclassOf<UUserWidget> GameWidgetClass;

	/* Класс виджета выигрыша */
	TSubclassOf<UUserWidget> WinWidgetClass;

	/* Класс виджета проигрыша */
	TSubclassOf<UUserWidget> LoseWidgetClass;

	/* Таймер */
	FTimerHandle TH_Play;

	/* Ссылка на игровой виджет */
	UPROPERTY(Transient)
	class UTIRGameWidget* GameWidgetRef;
};
