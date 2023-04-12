/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                             ������ ��������                                                               */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


#include "Widget/TIRHealthWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

/* ������������ */
void UTIRHealthWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

/* ���������� ������� ������� �� � ����� ���� */
void UTIRHealthWidget::SetHealthCurrentTB(float NewHealth)
{
	/* ���������� ����� ���������� */
	const float Proccent = NewHealth / HealthMax;

	/* ������������ ������� �������� �� float � Text */
	FText CurrentHP = SetNumberConvert(NewHealth);

	PB_Health->SetPercent(Proccent); // ��������� ������� ��
	TB_CurrentHP->SetText(CurrentHP); // ������ ����� �������� ��������
}

/* ���������� ������������ �� � ����� ���� */
void UTIRHealthWidget::SetHealthMaxTB(float NewMax)
{
	HealthMax = abs(NewMax);

	// ������������ ������������ �������� �� float � Text
	//FText MaxHP = SetNumberConvert(HealthMax);

	//TB_MaxHP->SetText(MaxHP); // ������ ����� ������������� ��������
}

/* �������������� ����� � ����� */
template<class T>
inline FText UTIRHealthWidget::SetNumberConvert(T Num)
{
	FString StrHealth = FString::FromInt(Num); // ������� ����� � ������
	FText TextHealth = FText::FromString(StrHealth); // ������� � ����

	return TextHealth;
}
