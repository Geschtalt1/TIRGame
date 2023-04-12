/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                         ���������� �������                                                                */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TIRHelperLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PLAYRIX_API UTIRHelperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/* ���������� ������ */
	UFUNCTION(BlueprintCallable, Category = "TIR Widget")
	static UUserWidget* SetWidgetGame(class APlayerController* PlayerController,
		TSubclassOf<UUserWidget> WidgetCreate, 
		class UUserWidget* WidgetRemove);

	/* ����� ������ */
	UFUNCTION(BlueprintCallable, Category = "TIR Enemy")
	static void SpawnEnemy(const int32 CountEnemy, int32& SuccessfulSpawn);

	/* ��������� ���� (���������� ����� � ���-�� ������) */
	UFUNCTION(BlueprintCallable, Category = "TIR Game")
	static void SetGameSetting(UGameInstance* GameInstance, int32 Minute, int32 Enemy);

	/* ��������� ������� ����� � ���� ��� ��� */
	UFUNCTION(BlueprintCallable, Category = "TIR Game")
	static bool SetPausedWidget(class APlayerController* PlayerController, bool bEnable);

};
