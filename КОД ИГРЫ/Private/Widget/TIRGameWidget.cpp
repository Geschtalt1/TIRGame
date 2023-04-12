/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                              ������� ������                                                               */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#include "Widget/TIRGameWidget.h"
#include "Components/TextBlock.h"

void UTIRGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

/* ���������� � ����� ���� ���-�� ���������� ������� */
void UTIRGameWidget::SetCountEnemy(int32 NewCount)
{
	/* ����������� �� ��� � ��������� ��� */
	const FString StrCount = FString::FromInt(NewCount);
	const FText TextCount = FText::FromString(StrCount);

	/* ���������� � ����� ���� ���-�� ���������� ������� */
	TB_EnemyCount->SetText(TextCount);
}

/* ���������� � ����� ���� ����� ����� */
void UTIRGameWidget::SetCountMinut(int32 NewMinut)
{
	/* ����������� �� ��� � ��������� ��� */
	const FString StrMinut = FString::FromInt(NewMinut);
	const FText TextMinut = FText::FromString(StrMinut);

	/* ���������� � ����� ���� ���-�� ����� */
	TB_Minute->SetText(TextMinut);
}

/* ���������� � ����� ���� ����� ������ */
void UTIRGameWidget::SetCountSecond(int32 NewSecond)
{
	/* ����������� �� ��� � ��������� ��� */
	const FString StrSecond = FString::FromInt(NewSecond);
	const FText TextSecond = FText::FromString(StrSecond);

	/* ���������� � ����� ���� ���-�� ������ */
	TB_Second->SetText(TextSecond);
}