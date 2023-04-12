/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                              ������                                                                       */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#include "Pawns/TIREnemyBase.h"

#include "TIRGameModeBase.h"
#include "Widget/TIRHealthWidget.h"
#include "Library/TIRHelperLibrary.h"

#include "PaperSprite.h"
#include "Sound/SoundBase.h"
#include "PaperSpriteComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Component/TIRTargetMovementComponent.h"

#include "UObject/ConstructorHelpers.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"

ATIREnemyBase::ATIREnemyBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetSphereRadius(128.0f);
	SetRootComponent(Sphere);

	SpriteEnemy = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Mischen"));
	SpriteEnemy->SetWorldRotation(FRotator(0.0f, 90.0f, 90.0f));
	SpriteEnemy->SetCollisionResponseToAllChannels(ECR_Ignore);
	SpriteEnemy->SetupAttachment(Sphere);

	MovementComponent = CreateDefaultSubobject<UTIRTargetMovementComponent>(TEXT("Movement"));

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Mischen Health"));
	HealthWidgetComponent->AttachToComponent(SpriteEnemy, FAttachmentTransformRules::KeepRelativeTransform);
	HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidgetComponent->SetDrawSize(FVector2D(64, 64));
	HealthWidgetComponent->SetTickMode(ETickMode::Automatic);
	HealthWidgetComponent->SetWorldLocation(FVector(60.0, 0.0, 0.0));
	HealthWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HealthWidgetComponent->SetGenerateOverlapEvents(false);

	HealthCurrent = 0.0f;
	HealthMax = 0.0f;

	HealthWidget = nullptr;


	static ConstructorHelpers::FClassFinder<UUserWidget> WB_HealthAsset(TEXT
	("/Game/Playerix/Widget/WB_HealthWidget"));

	static ConstructorHelpers::FObjectFinder<UPaperSprite> S_TargetAsset(TEXT
	("/Game/Playerix/Assets/Sprites/S_Target"));

	if (WB_HealthAsset.Succeeded())
		HealthWidgetComponent->SetWidgetClass(WB_HealthAsset.Class);

	if (S_TargetAsset.Succeeded())
		GetSpriteEnemyComponent()->SetSprite(S_TargetAsset.Object);

	SetActorRotation(FRotator(0.0f, 0.0f, -90.0f));

	Sphere->OnComponentHit.AddDynamic(this, &ATIREnemyBase::OnCompHit);
}

/* ������ ���� */
void ATIREnemyBase::BeginPlay()
{
	Super::BeginPlay();

	HealthWidget = Cast<UTIRHealthWidget>(HealthWidgetComponent->GetUserWidgetObject());

	if (IsValid(HealthWidget))
	{
		HealthWidget->SetHealthMaxTB(GetHealthMax()); // ��������� ������������ �������� �� � �������
		HealthWidget->SetHealthCurrentTB(GetHealthCurrent()); // ��������� ������� �������� �� � �������
	}
}

/* ���������� ������� ���-�� �������� ������ */
float ATIREnemyBase::SetHealthCurrent(const float NewHealth)
{
	HealthCurrent = FMath::Clamp(NewHealth, 0.0f, HealthMax); // �������� ����� �������� (NewHealth), ����� 0 � ������������ ���-�� ��

	if (GetHealthCurrent() <= 0.0f) // ���� �������� ������ ����� ���� 
		Dead(); // ��������� ������ ������
	
	return HealthCurrent; // ��������� ��
}

/* ���������� ������������ ���-�� �������� ������ */
void ATIREnemyBase::SetHealthMax(const float NewHealthMax)
{
	HealthMax = abs(NewHealthMax); // ����������� ����� �������, �������� NewHealthMax ����� ������ �������������
	
	if (GetHealthMax() < GetHealthCurrent()) // ���� ����. �� ������ �������� ��������, �� ������������� �������� �������� ������������ �������� ��
		SetHealthCurrent(HealthMax);
}

/* ���������� ������ ������ */
void ATIREnemyBase::SetSizeEnemy(const float NewSize)
{
	float SizeLocal = abs(NewSize); // �������� NewSize ����� ������ �������������

	SetActorScale3D(FVector(SizeLocal, // X
		SizeLocal,                     // Y
		SizeLocal));                   // Z
}

/* ���������� ���� ������ */
void ATIREnemyBase::SetColorEnemy(FLinearColor NewColor)
{
	GetSpriteEnemyComponent()->SetSpriteColor(NewColor); // ������ ���� �������
}

/* ��������� ����� */
float ATIREnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float NewHealth = FMath::Clamp(GetHealthCurrent() - DamageAmount, 
		0.0f, GetHealthMax()); // ����������� �� �������� ��������� ����
		
	SetHealthCurrent(NewHealth); // ������������� ����� �������� ��������

	if (IsValid(HealthWidget))
		HealthWidget->SetHealthCurrentTB(GetHealthCurrent());  // ��������� ������� �� � �������

	return DamageAmount;
}

/* ������������ ������� ���� �� ����� */
void ATIREnemyBase::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{		
		ATIREnemyBase* Mischen = Cast<ATIREnemyBase>(OtherActor); // ������ � ����� ������ ��������� ������

		if (Mischen)
		{
			// ���������� ���������� ����������� ������ � ������� ������
			FVector2D NewDirection = Mischen->GetMovementComponent()->GetDirectionMovement();

			// ������������� ����� ����������
			GetMovementComponent()->SetDirectionMovement(NewDirection);
		}
	}
}

/* ������ ������ */
void ATIREnemyBase::Dead()
{
	ATIRGameModeBase* GameModeLoc = Cast<ATIRGameModeBase>
		(UGameplayStatics::GetGameMode(GetWorld())); // ������ ���� ���

	// ������� ������
	HealthWidget = nullptr;

	if (GameModeLoc) // ���� ������ �� ���� ��� ����
		GameModeLoc->DeadEnemy(); // ��������� ������� � ���� ����
	Destroy(); // ������ ������������ � ������
}
