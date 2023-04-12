/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                             ������ ��������                                                               */
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
	/* ���������� ������� ������� �� � ����� ���� */
	UFUNCTION(BlueprintCallable, Category = "SET Health")
	void SetHealthCurrentTB(float NewHealth);

	/* ���������� ������������ �� � ����� ���� */
	UFUNCTION(BlueprintCallable, Category = "SET Health")
	void SetHealthMaxTB(float NewMax);

protected:
	/* �������������� ����� � ����� */
	template<class T>
	FText SetNumberConvert(T Num);

	/* ������������ */
	virtual void NativeConstruct() override;

protected:
	/* VARIEBLE */
	/* ������� �� */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* PB_Health;

	/* ����� ���� ������� �������� */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TB_CurrentHP;

	/* ���� ���� ������������� �������� */
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	//class UTextBlock* TB_MaxHP;

private:
	/* VARIEBLE */
	/* ������������ �� */
	UPROPERTY()
	float HealthMax;
};
