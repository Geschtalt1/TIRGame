/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                         БИБЛИОТЕКА ФУНКЦИЙ                                                                */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TIRHelperLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PLAYRIX_API UTIRHelperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/* Установить виджет */
	UFUNCTION(BlueprintCallable, Category = "TIR Widget")
	static UUserWidget* SetWidgetGame(class APlayerController* PlayerController,
		TSubclassOf<UUserWidget> WidgetCreate, 
		class UUserWidget* WidgetRemove);

	/* Спавн врагов */
	UFUNCTION(BlueprintCallable, Category = "TIR Enemy")
	static void SpawnEnemy(const int32 CountEnemy, int32& SuccessfulSpawn);

	/* Настройка игры (установить время и кол-во врагов) */
	UFUNCTION(BlueprintCallable, Category = "TIR Game")
	static void SetGameSetting(UGameInstance* GameInstance, int32 Minute, int32 Enemy);

	/* Разрешить ставить паузу в игре или нет */
	UFUNCTION(BlueprintCallable, Category = "TIR Game")
	static bool SetPausedWidget(class APlayerController* PlayerController, bool bEnable);

};
