/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                 РОДИТЕЛЬСКИЙ ВИДЖЕТ РЕЗУЛЬТАТОВ                                                           */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TIRResultWidget.generated.h"

/**
 * 
 */
UCLASS()
class PLAYRIX_API UTIRResultWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/* FUNCTION */
	/* Иницилизация */
	virtual void NativeConstruct() override;

private:
	/* FUNCTION */
	/* Рестарт уровня */
	UFUNCTION()
	void OnRestart();

	/* Выйти в меню игры */
	UFUNCTION()
	void OnExitMenu();

protected:
	/* VARIEBLE */
	/* Кнопка рестарта */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* B_Restart;

	/* Кнопка выхода */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* B_Exit;

private:
	/* VARIEBLE */
	/* Название уровня меню */
	const FName Menu = FName("Level_00");
	
};
