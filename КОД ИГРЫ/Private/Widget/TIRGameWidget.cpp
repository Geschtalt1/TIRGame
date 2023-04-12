/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                              ИГРОВОЙ ВИДЖЕТ                                                               */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#include "Widget/TIRGameWidget.h"
#include "Components/TextBlock.h"

void UTIRGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

/* Установить в текст бокс кол-во оставшихся мишеней */
void UTIRGameWidget::SetCountEnemy(int32 NewCount)
{
	/* Конвертация из инт в строковой тип */
	const FString StrCount = FString::FromInt(NewCount);
	const FText TextCount = FText::FromString(StrCount);

	/* Установить в текст бокс кол-во оставшихся мишеней */
	TB_EnemyCount->SetText(TextCount);
}

/* Установить в текст блок колво минут */
void UTIRGameWidget::SetCountMinut(int32 NewMinut)
{
	/* Конвертация из инт в строковой тип */
	const FString StrMinut = FString::FromInt(NewMinut);
	const FText TextMinut = FText::FromString(StrMinut);

	/* Установить в текст бокс кол-во минут */
	TB_Minute->SetText(TextMinut);
}

/* Установить в текст блок колво секунд */
void UTIRGameWidget::SetCountSecond(int32 NewSecond)
{
	/* Конвертация из инт в строковой тип */
	const FString StrSecond = FString::FromInt(NewSecond);
	const FText TextSecond = FText::FromString(StrSecond);

	/* Установить в текст бокс кол-во секунд */
	TB_Second->SetText(TextSecond);
}