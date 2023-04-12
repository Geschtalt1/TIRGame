/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                              ������� ������                                                               */
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
	/* ���������� � ����� ���� ���-�� ���������� ������� */
	virtual void SetCountEnemy(int32 NewCount);

	/* ���������� � ����� ���� ����� ����� */
	virtual void SetCountMinut(int32 NewMinut);

	/* ���������� � ����� ���� ����� ������ */
	virtual void SetCountSecond(int32 NewSecond);

protected:
	/* FUNCTION */
	/* ������������ */
	virtual void NativeConstruct() override;

protected:
	/* VARIEBLE */
	/* ����� ���� ���-�� ������� */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TB_EnemyCount;

	/* ����� ���� ���-�� ����� */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TB_Minute;

	/* ����� ���� ���-�� ������ */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TB_Second;
};
