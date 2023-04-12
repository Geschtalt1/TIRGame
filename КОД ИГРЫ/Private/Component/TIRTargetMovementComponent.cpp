/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                      ��������� �������� ������                                                            */
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

	OwnerMovement = Cast<ATIREnemyBase>(GetOwner()); // ������ �� ��������� �����������
	PlayerController = Cast<ATIRPlayerController>(UxGS::GetPlayerController(GetWorld(), 0)); // ������ �� ���������� ������

	if (!OwnerMovement || !PlayerController) // ���� ���� �� ������ ������
		GetOwner()->Destroy(); // ������ ������������ � ����

	//SetDirectionMovement(Vx2D(UxKML::SelectFloat(1.0f, -1.0f, UxKML::RandomBool()), // �������� ����������� �� X
		//UxKML::SelectFloat(1.0f, -1.0f, UxKML::RandomBool())));                    // ��������� ����������� �� Y

	FVector2D DirectionRand;
	RandomDirection(DirectionRand);
	SetDirectionMovement(DirectionRand);
}


// Called every frame
void UTIRTargetMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (MovementUpdateDelegate.IsBound()) // ��������� ��� ������� �������� � �������
		MovementUpdateDelegate.Execute(DeltaTime); // ��������� ������������ ������
	// ...
}

/* ���������� �������� ����������� */
void UTIRTargetMovementComponent::SetSpeedMovement(float NewSpeed)
{
	SpeedMovement = abs(NewSpeed); // �������� NewSpeed ����� ������ �������������
}

/* �������� ������ */
void UTIRTargetMovementComponent::MischenMovement(float DeltaTime)
{
	// �������� � ������� ��������� ������
	FVector Modifier = Vx3D(SpeedMovement * DeltaTime, SpeedMovement * DeltaTime, 0.0f);

	// ����������� ��������� ������ �� 3D � 2D
	FVector2D CurrentPosition;
	PlayerController->ProjectWorldLocationToScreen(GetOwnerMovement()->GetActorLocation(), CurrentPosition);

	// ������������ ������ �� ������
	float LocationX = CurrentPosition.X;
	float LocationY = CurrentPosition.Y;

	// ��������� ������ ������
	int32 ViewportSizeX;
	int32 ViewportSizeY;

	PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);

	// ������������ ���������
	float ProportionX = LocationX / ViewportSizeX;
	float ProportionY = LocationY / ViewportSizeY;

	GetOwnerMovement()->AddActorLocalOffset(Vx3D(Direction.X, Direction.Y, 0.0f) * Modifier, true); // ���������� ������

	FVector2D DirectRan;

	if (ProportionX <= .030) // ���� �������� ������ ����
	{
		RandomDirection(DirectRan);
		SetDirectionMovement(Vx2D(-1.0f, DirectRan.Y)); // ������ ���������� �� ������������� X
	}
	else if (ProportionX >= .970) // ���� �������� ������� ����
	{
		RandomDirection(DirectRan);
		SetDirectionMovement(Vx2D(1.0f, DirectRan.Y));// ������ ���������� �� ������������� X
	}
	else if (ProportionY >= .970) // ���� �������� ������� ����
	{
		RandomDirection(DirectRan);
		SetDirectionMovement(Vx2D(DirectRan.X, 1.0f)); // ������ ���������� �� ������������� Y
	}
	else if (ProportionY <= .030) // ���� �������� ������� ����
	{
		RandomDirection(DirectRan);
		SetDirectionMovement(Vx2D(DirectRan.X, -1.0f)); // ������ ���������� �� ������������� Y
	}
	else {}

#ifdef DebugDirection

	UxE->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Green, FString::Printf(TEXT("DirectionX: %f"), GetDirectionMovement().X));
	UxE->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Orange, FString::Printf(TEXT("DirectionY: %f"), GetDirectionMovement().Y));

#endif // 

}

/* ���������� ����������� ����������� */
void UTIRTargetMovementComponent::SetDirectionMovement(FVector2D NewDirection)
{
	Direction.X = UxKML::Clamp(NewDirection.X, -2.0, 2.0f);
	Direction.Y = UxKML::Clamp(NewDirection.Y, -2.0, 2.0f);
}

void UTIRTargetMovementComponent::RandomDirection(FVector2D& V)
{
	// ��������� ����������� ��������
	TArray<float> DirectionArray;

	DirectionArray.Add(-1.0f);
	DirectionArray.Add(0.0f);
	DirectionArray.Add(1.0f);

	FVector2D NewDirection;

	// ��������� ������� ���������� ����� ������ �����������
	NewDirection.X = DirectionArray[UxKML::RandomInteger(2)];
	NewDirection.Y = DirectionArray[UxKML::RandomInteger(2)];

	if (NewDirection.X == 0.0f && NewDirection.Y == 0.0f) // ���� ������ ������� ����������
		RandomDirection(NewDirection); // ��������� ������� �� �����

	V = NewDirection;
}