#include "Elements/CrystalProjectile.h"
#include "Kismet/GameplayStatics.h"	
#include "TheLandOfFey/TheLandOfFeyCharacter.h"

ACrystalProjectile::ACrystalProjectile()
{
	PrimaryActorTick.bCanEverTick = true;


	ElementSystem = CreateDefaultSubobject<UElementalAbilityComponent>(TEXT("ElementManager"));					//create ElemenalAbilityComponent

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));								//empty SceneComponent as root
	RootComponent = Root;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));						//create mesh
	CrystalCapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Crystal Capsule Collision"));		//create collider

	ProjectileMesh->SetupAttachment(RootComponent);																//attach mesh 
	CrystalCapsuleCollision->SetupAttachment(RootComponent);													//attach collider


	CrystalCapsuleCollision->OnComponentBeginOverlap.AddDynamic(this, &ACrystalProjectile::OnProjectileHit);	//bind function to overlap event

	CrystalCapsuleCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);									//setup collision presets
	CrystalCapsuleCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CrystalCapsuleCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CrystalCapsuleCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

}

void ACrystalProjectile::OnProjectileHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;														//if nothing hit, return

	ATheLandOfFeyCharacter* Player = Cast<ATheLandOfFeyCharacter>(OtherActor);		//make sure hit actor (OtherActor) is player and cast to player

    if (Player)
    {
        float DamageMultiplier = 1.0f;  // Default to normal damage

        FName AttackerElementName;
        FName DefenderElementName;

        if (this->ElementSystem)
        {
            AttackerElementName = this->ElementSystem->GetCurrentElement()->ElementDisplayName;  // Attacker is the projectile
        }
        if (Player->ElementSystem && Player->ElementSystem->GetCurrentElement() != nullptr )
        {
            DefenderElementName = Player->ElementSystem->GetCurrentElement()->ElementDisplayName;  // Defender is the player
        }

        // Get the damage multiplier from the matrix only if both attacker and defender have elements
        if (!AttackerElementName.IsNone() && !DefenderElementName.IsNone())
        {
            TPair<FName, FName> ElementPair = TPair<FName, FName>{ DefenderElementName, AttackerElementName };
            if (this->ElementSystem->ElementalDamageMatrix.Contains(ElementPair))
            {
                DamageMultiplier = this->ElementSystem->ElementalDamageMatrix[ElementPair];
            }
        }

        float ActualDamage = Projectile_Damage * DamageMultiplier;

        //---VFX--
        UWorld* World = GetWorld();
        FVector ParticleLocation = Player->GetActorLocation();
        ParticleLocation.Z += 60.0f;						//vertical offset (Z-Axis)
        FRotator ParticleRotation(0.f, 0.f, 0.f);
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraParticle_Light, ParticleLocation, ParticleRotation);

        //---SFX---
        Impact_SFX();

        //---DAMG--
        UGameplayStatics::ApplyDamage(
            Player,
            ActualDamage,
            GetInstigatorController(),
            this,
            UDamageType::StaticClass()
        );
    }
}

// Called when the game starts or when spawned
void ACrystalProjectile::BeginPlay()
{
	Super::BeginPlay();

	ElementSystem->InitElementManager();

    //---SFX---
    Shoot_SFX();
}

// Called every frame
void ACrystalProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

