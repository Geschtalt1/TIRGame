/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                      КОМПОНЕНТ ДВИЖЕНИЯ МИШЕНИ                                                            */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#include "Component/TIRTargetMovementComponent.h"

#include "Pawns/TIREnemyBase.h"
#include "TIRPlayerController.h"

#include "Math/Vector2D.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

typedef UKismetMathLibrary                 UxKML;
typedef UGameplayStatics                   UxGS;
typedef FVector                            Vx3D;
typedef FVector2D                          Vx2D;
typedef UEngine                            UxE;

// Sets default values for this component's properties
UTIRTargetMovementComponent::UTIRTargetMovementComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	SpeedMovement = 300.0f;
	OwnerMovement = nullptr;

	Direction = Vx2D{ 0 };

	MovementUpdateDelegate.BindUObject(this, &UTIRTargetMovementComponent::MischenMovement);

	// ...
}


// Called when the game starts
void UTIRTargetMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerMovement = Cast<ATIREnemyBase>(GetOwner()); // Ссылка на владельца компонентом
	PlayerController = Cast<ATIRPlayerController>(UxGS::GetPlayerController(GetWorld(), 0)); // Ссылка на контроллер игрока

	if (!OwnerMovement || !PlayerController) // Если одна из ссылак пустая
		GetOwner()->Destroy(); // Мишень уничтожается с мира

	//SetDirectionMovement(Vx2D(UxKML::SelectFloat(1.0f, -1.0f, UxKML::RandomBool()), // Случайно перемещение по X
		//UxKML::SelectFloat(1.0f, -1.0f, UxKML::RandomBool())));                    // Случайное перемещение по Y

	FVector2D DirectionRand;
	RandomDirection(DirectionRand);
	SetDirectionMovement(DirectionRand);
}


// Called every frame
void UTIRTargetMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (MovementUpdateDelegate.IsBound()) // Проверяем что делегат привязан к функции
		MovementUpdateDelegate.Execute(DeltaTime); // Обновляем передвижение мишени
	// ...
}

/* Установить скорость перемещения */
void UTIRTargetMovementComponent::SetSpeedMovement(float NewSpeed)
{
	SpeedMovement = abs(NewSpeed); // Значение NewSpeed будет всегда положительным
}

/* Движение мишени */
void UTIRTargetMovementComponent::MischenMovement(float DeltaTime)
{
	// Скорость с которой движеться мишень
	FVector Modifier = Vx3D(SpeedMovement * DeltaTime, SpeedMovement * DeltaTime, 0.0f);

	// Конвертация положения мишени из 3D в 2D
	FVector2D CurrentPosition;
	PlayerController->ProjectWorldLocationToScreen(GetOwnerMovement()->GetActorLocation(), CurrentPosition);

	// Расположение мишени на экране
	float LocationX = CurrentPosition.X;
	float LocationY = CurrentPosition.Y;

	// Возращаем размер экрана
	int32 ViewportSizeX;
	int32 ViewportSizeY;

	PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);

	// Рассчитываем пропорции
	float ProportionX = LocationX / ViewportSizeX;
	float ProportionY = LocationY / ViewportSizeY;

	GetOwnerMovement()->AddActorLocalOffset(Vx3D(Direction.X, Direction.Y, 0.0f) * Modifier, true); // Перемещаем мишень

	FVector2D DirectRan;

	if (ProportionX <= .030) // Если коснулся левого края
	{
		RandomDirection(DirectRan);
		SetDirectionMovement(Vx2D(-1.0f, DirectRan.Y)); // Меняем траекторию на отрицательный X
	}
	else if (ProportionX >= .970) // Если коснулся правого края
	{
		RandomDirection(DirectRan);
		SetDirectionMovement(Vx2D(1.0f, DirectRan.Y));// Меняем траекторию на положительный X
	}
	else if (ProportionY >= .970) // Если коснулся нижнего края
	{
		RandomDirection(DirectRan);
		SetDirectionMovement(Vx2D(DirectRan.X, 1.0f)); // Меняем траекторию на положительный Y
	}
	else if (ProportionY <= .030) // Если коснулся нижнего края
	{
		RandomDirection(DirectRan);
		SetDirectionMovement(Vx2D(DirectRan.X, -1.0f)); // Меняем траекторию на отрицательный Y
	}
	else {}

#ifdef DebugDirection

	UxE->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Green, FString::Printf(TEXT("DirectionX: %f"), GetDirectionMovement().X));
	UxE->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Orange, FString::Printf(TEXT("DirectionY: %f"), GetDirectionMovement().Y));

#endif // 

}

/* Установить направление перемещения */
void UTIRTargetMovementComponent::SetDirectionMovement(FVector2D NewDirection)
{
	Direction.X = UxKML::Clamp(NewDirection.X, -2.0, 2.0f);
	Direction.Y = UxKML::Clamp(NewDirection.Y, -2.0, 2.0f);
}

void UTIRTargetMovementComponent::RandomDirection(FVector2D& V)
{
	// Возможные направления движения
	TArray<float> DirectionArray;

	DirectionArray.Add(-1.0f);
	DirectionArray.Add(0.0f);
	DirectionArray.Add(1.0f);

	FVector2D NewDirection;

	// Случайным образом определяем новый вектор перемещения
	NewDirection.X = DirectionArray[UxKML::RandomInteger(2)];
	NewDirection.Y = DirectionArray[UxKML::RandomInteger(2)];

	if (NewDirection.X == 0.0f && NewDirection.Y == 0.0f) // Если выпали нулевые координаты
		RandomDirection(NewDirection); // Запускаем функцию по новой

	V = NewDirection;
}