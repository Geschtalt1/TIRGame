/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                           ¿Ã≈–¿ »√–Œ ¿                                                                    */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


#include "TIRPlayerCamera.h"
#include "Camera/CameraComponent.h"

// Sets default values
ATIRPlayerCamera::ATIRPlayerCamera(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	CameraPlayer = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SetRootComponent(CameraPlayer);

}

