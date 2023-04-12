// Fill out your copyright notice in the Description page of Project Settings.
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                              ������                                                                       */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#include "TIRGunBase.h"

#include "GameFramework/PlayerController.h"
#include "Components/SceneComponent.h"
#include "Other/TIRProjectile.h"
#include "TIRPlayerController.h"
#include "PaperSpriteComponent.h"
#include "Sound/SoundBase.h"
#include "PaperSprite.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATIRGunBase::ATIRGunBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	DefaultScene = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(DefaultScene); 

	SpriteGun = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Weapon"));
	SpriteGun->SetWorldRotation(FRotator(90.0f, 0.0f, 0.0f));
	SpriteGun->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
	SpriteGun->SetupAttachment(DefaultScene);

	SpriteMuzzle = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Muzzle"));
	SpriteMuzzle->SetWorldLocation(FVector(1450.0f, 0.0f, 150.0f));
	SpriteMuzzle->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpriteMuzzle->SetVisibility(false);
	SpriteMuzzle->SetupAttachment(SpriteGun);

	FireSound = nullptr;

	Dammage = 25.0f;
	FireRate = 0.2f;

	static ConstructorHelpers::FObjectFinder<UPaperSprite> S_RifaleAsset(TEXT
	("/Game/Playerix/Assets/Sprites/S_Rifle_01"));

	static ConstructorHelpers::FObjectFinder<UPaperSprite> S_MuzzleAsset(TEXT
	("/Game/Playerix/Assets/Sprites/S_Muzzle"));

	static ConstructorHelpers::FObjectFinder<USoundBase> S_SoundAsset(TEXT
	("/Game/Playerix/Assets/Sound/SW_GunShot_01"));

	if (S_SoundAsset.Succeeded())
		SetSoudFire(S_SoundAsset.Object);

	if (S_MuzzleAsset.Succeeded())
		SpriteMuzzle->SetSprite(S_MuzzleAsset.Object);

	if (S_RifaleAsset.Succeeded())
		GetSpriteGunComponent()->SetSprite(S_RifaleAsset.Object);

	RotationUpdateDelegat.BindUObject(this, &ATIRGunBase::RotationUpdate);
}

// Called when the game starts or when spawned
void ATIRGunBase::BeginPlay()
{
	Super::BeginPlay();

	// ������ �� ���������� ������
	ATIRPlayerController* PlayerRef = Cast<ATIRPlayerController>
		(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	// ���� ������ �� ����� � ���������� ������
	if (IsValid(PlayerRef))
		PlayerRef->SetWeapon(this);
}

// Called every frame
void ATIRGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (RotationUpdateDelegat.IsBound()) // ��������� ��� ������� �������� � �������
		RotationUpdateDelegat.Execute(); // ��������� ��������

}

/* �������� ������ */
void ATIRGunBase::RotationUpdate()
{

	// ������������ ������� ����
	FHitResult Hit;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursorByChannel(TraceTypeQuery1, true, Hit);

	// ������� ���������� ����� 
	FVector LocationLocal = GetActorLocation();

	// ������� ����� �������
	float X = Hit.Location.X - LocationLocal.X;
	float Z = Hit.Location.Z - LocationLocal.Z;

	float NewRotation = UKismetMathLibrary::DegAtan2(X, Z) * (-1.0f);

	// ������������� �������
	SetActorRotation(FRotator(NewRotation, 0.0f, 0.0f));
}

/* ���������� ���������������� ������ */
void ATIRGunBase::SetFireRate(float NewFireRate)
{
	FireRate = FMath::Clamp(NewFireRate, 0.0f, 1.0f);
}

/* ���������� ��������� ���� ����� */
void ATIRGunBase::SetDammage(float NewDammage)
{
	Dammage = abs(NewDammage);
}

/* ���������� ���� �������� */
void ATIRGunBase::SetSoudFire(USoundBase* NewSound)
{
	FireSound = NewSound;
}

/* �������� �� ����� */
void ATIRGunBase::OnFire()
{
	// ���������� ���������� ������ 
	FVector SocketLoc = GetSpriteGunComponent()->GetSocketLocation(FName("BulletSocket"));

	// ����� �������
	FTransform SpawnTransform = FTransform(GetActorRotation(), SocketLoc);
	ATIRProjectile* Bullet = GetWorld()->SpawnActorDeferred<ATIRProjectile>(ATIRProjectile::StaticClass(), 
		SpawnTransform);
	
	if (IsValid(Bullet)) /* ����������� */
	{
		Bullet->SetBulletDammage(GetDammage());
		UGameplayStatics::FinishSpawningActor(Bullet, SpawnTransform); /* ��������� ����� */
	}

	// �������
	EffectMuzzle();

	// ������������� ���� ��������
	if (GetSoudFire())
		UGameplayStatics::PlaySound2D(this, GetSoudFire(),  1.0f,
			UKismetMathLibrary::RandomFloatInRange(0.9f, 1.0f));
}

/* ������� ��� �������� */
void ATIRGunBase::EffectMuzzle()
{
	// ������� �������
	SetMuzzleVisible(true);

	// ��������� ������� ����� 0.1 ���
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &ATIRGunBase::SetMuzzleVisible, false);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 0.1, false);
}

/* ������� ��� ������ ������ ������� */
void ATIRGunBase::SetMuzzleVisible(bool bVisible)
{
	SpriteMuzzle->SetVisibility(bVisible);
}

