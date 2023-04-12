/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                           ¿Ã≈–¿ »√–Œ ¿                                                                    */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TIRPlayerCamera.generated.h"

UCLASS()
class PLAYRIX_API ATIRPlayerCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATIRPlayerCamera(const FObjectInitializer& ObjectInitializer);

public:
	/*  ‡ÏÂ‡ Ë„ÓÍ‡ */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UCameraComponent* CameraPlayer;

};
