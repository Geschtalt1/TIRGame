/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                      КОНТРОЛЛЕР ИГРОКА                                                                    */
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

/* Управление */
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
		/* Устанавливаем игровой ввод */
		FInputModeGameAndUI InputModeDate;
		InputModeDate.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		InputModeDate.SetHideCursorDuringCapture(false);

		SetInputMode(InputModeDate);

		bPauseEnable = true;
	}
}

/* Автоматическая стрельба */
void ATIRPlayerController::OnFiring()
{
	// Таймер работате пока нажата левая кнопка мыши
	if (IsValid(GetWeapon()))
		GetWorldTimerManager().SetTimer(TH_AutoFiring, this,
			&ATIRPlayerController::CallShoot, GetWeapon()->GetFireRate(), true, 0.0f);
}

/* Стрельба из пушки */
void ATIRPlayerController::CallShoot()
{
	if (IsValid(GetWeapon())) // Если пушка у игрока есть
		GetWeapon()->OnFire(); // Стреляем из пушки
}

/* Остановить стрельбу */
void ATIRPlayerController::StopShoot()
{
	// Отключаем таймер
	GetWorldTimerManager().PauseTimer(TH_AutoFiring);
	GetWorldTimerManager().ClearTimer(TH_AutoFiring);
}

/* Пауза */
void ATIRPlayerController::CallPause()
{
	if (IsValid(WidgetPause) && bPauseEnable) // Если класс виджета выбран и пауза разрешена
	{
		if (!IsValid(WidgetReference)) // Если виджет не создан
		{
			WidgetReference = UTIRHelperLibrary::SetWidgetGame(this, WidgetPause, nullptr); // Создаем виджет
			UGameplayStatics::SetGamePaused(this, true); // Ставим игру на паузу
		}
		else if (IsValid(WidgetReference) && WidgetReference->IsInViewport()) // Если виджет создан и выведен на экран 
		{
			UTIRHelperLibrary::SetWidgetGame(this, nullptr, WidgetReference); // Удаляем виджет
			UGameplayStatics::SetGamePaused(this, false); // Снимаем паузу
			WidgetReference = nullptr; // Очищаем ссылку
		}
		else // В остальных случаях
		{
			WidgetReference = UTIRHelperLibrary::SetWidgetGame(this, WidgetPause, nullptr); // Создаем виджет
			UGameplayStatics::SetGamePaused(this, true); // Ставим паузу
		}

		StopShoot();
	}
}

/* Установить ссылку на пушку */
void ATIRPlayerController::SetWeapon(ATIRGunBase* NewWeapon)
{
	GunReference = NewWeapon;
}