/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                 ������������ ������ �����������                                                           */
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
	/* ������������ */
	virtual void NativeConstruct() override;

private:
	/* FUNCTION */
	/* ������� ������ */
	UFUNCTION()
	void OnRestart();

	/* ����� � ���� ���� */
	UFUNCTION()
	void OnExitMenu();

protected:
	/* VARIEBLE */
	/* ������ �������� */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* B_Restart;

	/* ������ ������ */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* B_Exit;

private:
	/* VARIEBLE */
	/* �������� ������ ���� */
	const FName Menu = FName("Level_00");
	
};
