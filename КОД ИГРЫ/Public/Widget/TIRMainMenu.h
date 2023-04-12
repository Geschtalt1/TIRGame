/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                       ВИДЖЕТ ГЛАВНОГО МЕНЮ                                                                */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TIRMainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PLAYRIX_API UTIRMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/* FUNCTION */
	/* Иницилизация */
	virtual void NativeConstruct() override;

private:
	/* Играть */
	UFUNCTION()
	void OnPlayGame();

	/* Выйти с игры */
	UFUNCTION()
	void OnExitGame();

public:
	/* VARIABLE */
	/* Кнопка играть */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* B_Play;

	/* Кнопка выхода */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* B_Exit;

private:
	/* Геймплейный уровень */
	const FName GameLevel = FName("Level_01");
};
