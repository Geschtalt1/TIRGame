/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                      ���������� ������                                                                    */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#include "TIRPlayerController.h"
#include "TIRGunBase.h"
#include "Library/TIRHelperLibrary.h"

#include "Kismet/GameplayStatics.h"

#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

ATIRPlayerController::ATIRPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	bPauseEnable = true;

	WidgetPause = nullptr;
	WidgetReference = nullptr;

	static ConstructorHelpers::FClassFinder<UUserWidget> WB_PauseAsset(TEXT
	("/Game/Playerix/Widget/WB_Pause"));

	if (WB_PauseAsset.Succeeded())
		WidgetPause = WB_PauseAsset.Class;

}

/* ���������� */
void ATIRPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// 
	check(InputComponent);

	FInputActionBinding& Shoot = InputComponent->BindAction("Shoot", IE_Pressed, this, &ATIRPlayerController::OnFiring);
	FInputActionBinding& StopShoot = InputComponent->BindAction("Shoot", IE_Released, this, &ATIRPlayerController::StopShoot);
	FInputActionBinding& Pause = InputComponent->BindAction("Pause", IE_Pressed, this, &ATIRPlayerController::CallPause);
	
	Shoot.bExecuteWhenPaused = false;
	StopShoot.bExecuteWhenPaused = false;
	Pause.bExecuteWhenPaused = true;
}

// Called when the game starts or when spawned
void ATIRPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		/* ������������� ������� ���� */
		FInputModeGameAndUI InputModeDate;
		InputModeDate.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		InputModeDate.SetHideCursorDuringCapture(false);

		SetInputMode(InputModeDate);

		bPauseEnable = true;
	}
}

/* �������������� �������� */
void ATIRPlayerController::OnFiring()
{
	// ������ �������� ���� ������ ����� ������ ����
	if (IsValid(GetWeapon()))
		GetWorldTimerManager().SetTimer(TH_AutoFiring, this,
			&ATIRPlayerController::CallShoot, GetWeapon()->GetFireRate(), true, 0.0f);
}

/* �������� �� ����� */
void ATIRPlayerController::CallShoot()
{
	if (IsValid(GetWeapon())) // ���� ����� � ������ ����
		GetWeapon()->OnFire(); // �������� �� �����
}

/* ���������� �������� */
void ATIRPlayerController::StopShoot()
{
	// ��������� ������
	GetWorldTimerManager().PauseTimer(TH_AutoFiring);
	GetWorldTimerManager().ClearTimer(TH_AutoFiring);
}

/* ����� */
void ATIRPlayerController::CallPause()
{
	if (IsValid(WidgetPause) && bPauseEnable) // ���� ����� ������� ������ � ����� ���������
	{
		if (!IsValid(WidgetReference)) // ���� ������ �� ������
		{
			WidgetReference = UTIRHelperLibrary::SetWidgetGame(this, WidgetPause, nullptr); // ������� ������
			UGameplayStatics::SetGamePaused(this, true); // ������ ���� �� �����
		}
		else if (IsValid(WidgetReference) && WidgetReference->IsInViewport()) // ���� ������ ������ � ������� �� ����� 
		{
			UTIRHelperLibrary::SetWidgetGame(this, nullptr, WidgetReference); // ������� ������
			UGameplayStatics::SetGamePaused(this, false); // ������� �����
			WidgetReference = nullptr; // ������� ������
		}
		else // � ��������� �������
		{
			WidgetReference = UTIRHelperLibrary::SetWidgetGame(this, WidgetPause, nullptr); // ������� ������
			UGameplayStatics::SetGamePaused(this, true); // ������ �����
		}

		StopShoot();
	}
}

/* ���������� ������ �� ����� */
void ATIRPlayerController::SetWeapon(ATIRGunBase* NewWeapon)
{
	GunReference = NewWeapon;
}