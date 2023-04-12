/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                             ВИДЖЕТ ЗДОРОВЬЯ                                                               */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TIRHealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class PLAYRIX_API UTIRHealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/* FUNCTION */
	/* Установить текущее текущее ХП в текст блок */
	UFUNCTION(BlueprintCallable, Category = "SET Health")
	void SetHealthCurrentTB(float NewHealth);

	/* Установить максимальное ХП в текст блок */
	UFUNCTION(BlueprintCallable, Category = "SET Health")
	void SetHealthMaxTB(float NewMax);

protected:
	/* Конвертировать число в текст */
	template<class T>
	FText SetNumberConvert(T Num);

	/* Иницилизация */
	virtual void NativeConstruct() override;

protected:
	/* VARIEBLE */
	/* Полоска ХП */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* PB_Health;

	/* Текст блок текущее здоровье */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TB_CurrentHP;

	/* Текс блок максимального здоровья */
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	//class UTextBlock* TB_MaxHP;

private:
	/* VARIEBLE */
	/* Максимальное ХП */
	UPROPERTY()
	float HealthMax;
};
