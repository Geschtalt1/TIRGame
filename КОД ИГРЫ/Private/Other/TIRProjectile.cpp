/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                              ПУЛЯ                                                                         */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#include "Other/TIRProjectile.h"
#include "Pawns/TIREnemyBase.h"

#include "Components/SphereComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

// Sets default values
ATIRProjectile::ATIRProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	SphereBullet = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SphereBullet->SetCollisionObjectType(ECC_WorldStatic);
	SphereBullet->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SetRootComponent(SphereBullet);

	SpriteProjectile = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Bullet"));
	SpriteProjectile->SetCollisionResponseToAllChannels(ECR_Ignore);
	SpriteProjectile->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));
	SpriteProjectile->SetupAttachment(SphereBullet);

	InitialLifeSpan = 5.0f; // Время жизни 5 секунд
	BulletDammage = 0.0f;
	BulletSpeed = 1000.0f;

	static ConstructorHelpers::FObjectFinder<UPaperSprite> S_BulletAsset(TEXT
	("/Game/Playerix/Assets/Sprites/S_Bullet"));

	if (S_BulletAsset.Succeeded())
		SpriteProjectile->SetSprite(S_BulletAsset.Object);

	SphereBullet->OnComponentBeginOverlap.AddDynamic(this, &ATIRProjectile::OnOverlapBegin);
}

// Called every frame
void ATIRProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/* Перемещаем пулю */
	AddActorLocalOffset(FVector(0.0f,0.0, GetBulletSpeed() * DeltaTime));
}

/* Установить урон пули */
void ATIRProjectile::SetBulletDammage(float NewDammage)
{
	BulletDammage = abs(NewDammage);
}

void ATIRProjectile::SetBulletSpeed(float NewSpeed)
{
	BulletSpeed = abs(NewSpeed);
}

/* Попадание по мишени */
void ATIRProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		ATIREnemyBase* MischenHit = Cast<ATIREnemyBase>(OtherActor); // Ссылка в какую мишень попала пуля

		if (MischenHit)
		{
			MischenHit->TakeDamage(GetBulletDammage(), FDamageEvent(), nullptr, nullptr); // Наносим урон мишени
			Destroy(); // Уничтожаем пулю
		}
	}
}
