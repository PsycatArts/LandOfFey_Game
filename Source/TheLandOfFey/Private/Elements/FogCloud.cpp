#include "Elements/FogCloud.h"
#include "Kismet/GameplayStatics.h"	
#include "TheLandOfFey/TheLandOfFeyCharacter.h"


AFogCloud::AFogCloud()
{
	PrimaryActorTick.bCanEverTick = true;

	ElementSystem = CreateDefaultSubobject<UElementalAbilityComponent>(TEXT("ElementManager"));					//create ElemenalAbilityComponent

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));								//empty SceneComponent as root
	RootComponent = Root;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Fog Cloud Collision"));						//create collider
	SphereCollider->SetupAttachment(RootComponent);													            //attach collider
    SphereCollider->SetGenerateOverlapEvents(true);

	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AFogCloud::OnFogCloudEnter);	                    //bind function to begin overlap event
}

//AFogCloud::~AFogCloud()
//{
//    Super::BeginDestroy();
//
//  //  GetWorld()->GetTimerManager().ClearTimer(FogCloudTimerHandle);
//}

void AFogCloud::BeginPlay()
{
	Super::BeginPlay();

    ElementSystem->InitElementManager();

    SphereCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);		    //setup collision presets
    SphereCollider->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    SphereCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SphereCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
    SphereCollider->UpdateOverlaps();

    SpawnPreview();
}

void AFogCloud::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    //if player inside..
    if (!IsPlayerOutside())
    {
        //do sth

    }
}

//spawn preview & 1 sec after, the fog cloud
void AFogCloud::SpawnPreview()                  //spawn preview of fog cloud, to indicate the cloud spawning
{
    //---VFX--
    UWorld* World = GetWorld();
    FRotator ParticleRotation(0.f, 0.f, 0.f);
    UNiagaraFunctionLibrary::SpawnSystemAttached(NiagaraParticle_FogPreview, this->RootComponent, NAME_None, GetActorLocation(), ParticleRotation, EAttachLocation::KeepWorldPosition, false);

    //---SFX--
    Fog_SFX();

    GetWorld()->GetTimerManager().SetTimer(FogCloudTimerHandle, this, &AFogCloud::SpawnFogCloud, 0.5f);
}

//spawn fog cloud & activate collider
void AFogCloud::SpawnFogCloud()
{
    SphereCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    //---VFX--
    UWorld* World = GetWorld();
    FRotator ParticleRotation(0.f, 0.f, 0.f);
    UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(NiagaraParticle_FogCloud, this->RootComponent, NAME_None, GetActorLocation(), ParticleRotation, EAttachLocation::KeepWorldPosition, false);

    // Optional: In case you want to control when to stop the system, you can stop it by calling
   // NiagaraComponent->DeactivateSystem();
}

void AFogCloud::ApplyFogDamage()
{
    ATheLandOfFeyCharacter* Player = Cast<ATheLandOfFeyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    if (Player && !IsPlayerOutside())
    {
        float DamageMultiplier = 1.0f;                                                                  // Default to normal damage
        FName AttackerElementName;
        FName DefenderElementName;

        if (this->ElementSystem->GetCurrentElement() != nullptr)
        {
            AttackerElementName = this->ElementSystem->GetCurrentElement()->ElementDisplayName;         // Attacker is the projectile
        }
        if (Player->ElementSystem && Player->ElementSystem->GetCurrentElement() != nullptr)
        {
            DefenderElementName = Player->ElementSystem->GetCurrentElement()->ElementDisplayName;       // Defender is the player
        }

        if (!AttackerElementName.IsNone() && !DefenderElementName.IsNone())                              // Get the damage multiplier from the matrix only if both attacker and defender have elements
        {
            TPair<FName, FName> ElementPair = TPair<FName, FName>{ DefenderElementName, AttackerElementName };
            if (this->ElementSystem->ElementalDamageMatrix.Contains(ElementPair))
            {
                DamageMultiplier = this->ElementSystem->ElementalDamageMatrix[ElementPair];
            }
        }

        float ActualDamage = FogCloud_Damage * DamageMultiplier;

        //---VFX--
        if (NiagaraParticle_Impact_Dark)
        {

            UWorld* World = GetWorld();
            FVector ParticleLocation = Player->GetActorLocation();
            ParticleLocation.Z += 60.0f;
            FRotator ParticleRotation(0.f, 0.f, 0.f);
            UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraParticle_Impact_Dark, ParticleLocation, ParticleRotation);
        }


        UGameplayStatics::ApplyDamage(
            Player,
            ActualDamage,
            GetInstigatorController(),
            this,
            UDamageType::StaticClass()
        );
    }
}

void AFogCloud::OnFogCloudEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!OtherActor) return;

    ATheLandOfFeyCharacter* Player = Cast<ATheLandOfFeyCharacter>(OtherActor);
    if (!Player) return;

    //Apply damage once immediately
    ApplyFogDamage();

    //Start recurring timer to apply damage every 0.5 seconds
    GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle, this, &AFogCloud::ApplyFogDamage, 0.5f, true);

}

bool AFogCloud::IsPlayerOutside()
{
    ATheLandOfFeyCharacter* Player = Cast<ATheLandOfFeyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    if (Player && SphereCollider)
    {
        float Distance = FVector::Dist(Player->GetActorLocation(), SphereCollider->GetComponentLocation());

        if (Distance > SphereCollider->GetScaledSphereRadius())
        {
            //layer has exited the sphere
            //Clear recurring timer
            GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
            return true;
        }
    }
    return false;

}

