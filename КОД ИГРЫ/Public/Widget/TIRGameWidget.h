/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                              ИГРОВОЙ ВИДЖЕТ                                                               */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TIRGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class PLAYRIX_API UTIRGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/* SETTERS */
	/* Установить в текст бокс кол-во оставшихся мишеней */
	virtual void SetCountEnemy(int32 NewCount);

	/* Установить в текст блок колво минут */
	virtual void SetCountMinut(int32 NewMinut);

	/* Установить в текст блок колво секунд */
	virtual void SetCountSecond(int32 NewSecond);

protected:
	/* FUNCTION */
	/* Иницилизация */
	virtual void NativeConstruct() override;

protected:
	/* VARIEBLE */
	/* Текст блок Кол-во мишеней */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TB_EnemyCount;

	/* Текст блок Кол-во минут */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TB_Minute;

	/* Текст блок Кол-во секунд */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TB_Second;
};
