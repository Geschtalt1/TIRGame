/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                       ������ �������� ����                                                                */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TIRMainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PLAYRIX_API UTIRMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/* FUNCTION */
	/* ������������ */
	virtual void NativeConstruct() override;

private:
	/* ������ */
	UFUNCTION()
	void OnPlayGame();

	/* ����� � ���� */
	UFUNCTION()
	void OnExitGame();

public:
	/* VARIABLE */
	/* ������ ������ */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* B_Play;

	/* ������ ������ */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* B_Exit;

private:
	/* ����������� ������� */
	const FName GameLevel = FName("Level_01");
};
