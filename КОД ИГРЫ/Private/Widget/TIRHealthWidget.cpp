/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                             ВИДЖЕТ ЗДОРОВЬЯ                                                               */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


#include "Widget/TIRHealthWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

/* Иницилизация */
void UTIRHealthWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

/* Установить текущее текущее ХП в текст блок */
void UTIRHealthWidget::SetHealthCurrentTB(float NewHealth)
{
	/* Определяем шкалу заполнения */
	const float Proccent = NewHealth / HealthMax;

	/* Конвертируем текущее здоровье из float в Text */
	FText CurrentHP = SetNumberConvert(NewHealth);

	PB_Health->SetPercent(Proccent); // Обновляем полоску ХП
	TB_CurrentHP->SetText(CurrentHP); // Меняем цифры текущего здоровья
}

/* Установить максимальное ХП в текст блок */
void UTIRHealthWidget::SetHealthMaxTB(float NewMax)
{
	HealthMax = abs(NewMax);

	// Конвертируем максимальное здоровье из float в Text
	//FText MaxHP = SetNumberConvert(HealthMax);

	//TB_MaxHP->SetText(MaxHP); // Меняем цифры максимального здоровья
}

/* Конвертировать число в текст */
template<class T>
inline FText UTIRHealthWidget::SetNumberConvert(T Num)
{
	FString StrHealth = FString::FromInt(Num); // Конверт числа в строку
	FText TextHealth = FText::FromString(StrHealth); // Конверт в текс

	return TextHealth;
}
