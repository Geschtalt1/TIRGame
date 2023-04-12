/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                                 HUD                                                                       */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#pragma once

#include "CoreMinimal.h"
#include "TIRGameModeBase.h"
#include "GameFramework/HUD.h"
#include "TIRHudBase.generated.h"

/**
 * 
 */
UCLASS()
class PLAYRIX_API ATIRHudBase : public AHUD
{
	GENERATED_BODY()

public:
	/* Конструктор */
	ATIRHudBase(const FObjectInitializer& ObjectInitializer);
};
