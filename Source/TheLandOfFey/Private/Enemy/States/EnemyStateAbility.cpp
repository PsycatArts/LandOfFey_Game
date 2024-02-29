#include "Enemy/States/EnemyStateAbility.h"
#include "Enemy/EnemyAIController.h"
#include "NavigationSystem.h"

void UEnemyStateAbility::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

	ChooseAbility();
}

void UEnemyStateAbility::TickState()
{
	Super::TickState();
}

void UEnemyStateAbility::OnExitState()
{
	Super::OnExitState();

	GetWorld()->GetTimerManager().ClearTimer(MoveAwayTimer);
	GetWorld()->GetTimerManager().ClearTimer(AbilityResetTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(FogTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(FogSpawnTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(CrystalTimerHandle);
}

void UEnemyStateAbility::BackToCombatWrapper()
{
	BackToCombat();
}

void UEnemyStateAbility::ChooseAbility()
{
	UElementBase* AnyElement = Fey->ElementSystem->GetCurrentElement();

	if (!AnyElement) return;

	float DistanceToPlayer = FVector::Dist(Fey->GetActorLocation(), Player->GetActorLocation());

	//LIGHT
	if (AnyElement->ElementDisplayName == "Light")
	{
		if (DistanceToPlayer < MinProjectileDistance )
		{
			MoveAwayFromPlayer();
		}
		GetWorld()->GetTimerManager().SetTimer(MoveAwayTimer, this, &UEnemyStateAbility::LightAbility, 1.f, false);		//spawn Light projectile
	}
	//DARK
	else if (AnyElement->ElementDisplayName == "Dark")
	{
		// If the Fog Cloud already exists, do not use the ability. Switch back to combat state to choose another action
		if (SpawnedFogActor)
		{
			BackToCombat();
			return;
		}
		// If not, proceed with using the ability
		DarkAbility();
	}
}

//---DARK ABILITY: FOG CLOUD ----
void UEnemyStateAbility::DarkAbility()
{
	//---SFX---
	Fey->DarkAbility_Windup_SFX();

	//---ANIM---
	UAnimInstance* AnimInstance = Fey->GetMesh()->GetAnimInstance();

	if (FeyAnimInstance && DarkAbility_Montage)
	{
		FeyAnimInstance->Montage_Play(DarkAbility_Montage);
	}

	Fey->RotateTowardsPlayer();
	
	DestroyFog();						//if Fog exists, destroy previous																			

	GetWorld()->GetTimerManager().SetTimer(FogSpawnTimerHandle, this, &UEnemyStateAbility::SpawnFog, ProjectileSpawnAfter, false);
	GetWorld()->GetTimerManager().SetTimer(FogTimerHandle, this, &UEnemyStateAbility::DestroyProjectile, DestroyFogTime, false);			//destroy fog
	GetWorld()->GetTimerManager().SetTimer(AbilityResetTimerHandle, this, &UEnemyStateAbility::BackToCombat, AbilityDuration, false);		//exit state
}

void UEnemyStateAbility::SpawnFog()
{
	if (DarkAbility_ToSpawn) 
	{
		FVector SpawnLocation = Fey->GetActorLocation() + Fey->GetActorForwardVector() * 200.0f;
		FRotator SpawnRotation = Fey->GetActorRotation();

		SpawnedFogActor = GetWorld()->SpawnActor<AActor>(DarkAbility_ToSpawn, SpawnLocation, SpawnRotation);
	}
}

void UEnemyStateAbility::DestroyFog()
{
	if (SpawnedFogActor == nullptr)
	{
		return;
	}
	else
	{
		//vfx & SFX
		SpawnedFogActor->Destroy();
		SpawnedFogActor = nullptr;
	}
}

//---LIGHT ABILITY: CRYSTAL PROJECTILE ----
void UEnemyStateAbility::LightAbility()
{
	Fey->LightAbility_Windup_SFX();

	if (FeyAnimInstance && LightAbility_Montage)
	{
		Fey->RotateTowardsPlayer();
		FeyAnimInstance->Montage_Play(LightAbility_Montage);
	}
	
	DestroyProjectile();										//if projectile exists, destroy previous

	GetWorld()->GetTimerManager().SetTimer(CrystalTimerHandle, this, &UEnemyStateAbility::SpawnProjectile, ProjectileSpawnAfter, false);				//spawn obj
	GetWorld()->GetTimerManager().SetTimer(FogTimerHandle, this, &UEnemyStateAbility::DestroyProjectile, DestroyProjectileTime, false);				//destroy fog
	GetWorld()->GetTimerManager().SetTimer(AbilityResetTimerHandle, this, &UEnemyStateAbility::BackToCombat, AbilityDuration, false);				//exit state
}

void UEnemyStateAbility::SpawnProjectile()
{
	Fey->RotateTowardsPlayer();

	if (CrystalToSpawn)
	{
		//spawn projectile
		FVector SpawnLocation = Fey->GetActorLocation() + Fey->GetActorForwardVector() * 5.f;
		FRotator SpawnRotation = Fey->GetActorRotation();

		SpawnedProjectileActor = GetWorld()->SpawnActor<AActor>(CrystalToSpawn, SpawnLocation, SpawnRotation);
	}
}

void UEnemyStateAbility::DestroyProjectile()
{
	if (SpawnedProjectileActor == nullptr)
	{
		return;
	}
	else
	{
		//vfx  & SFX
		SpawnedProjectileActor->Destroy();
		SpawnedProjectileActor = nullptr;
	}
}

//---GENERAL----
void UEnemyStateAbility::MoveAwayFromPlayer()
{
	FVector Direction = Fey->GetActorLocation() - Player->GetActorLocation();
	Direction.Normalize();

	FVector Destination = Fey->GetActorLocation() + Direction * 400;

	FNavLocation ProjectedDestination;

	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(Fey->GetWorld());
	if (NavSystem && NavSystem->ProjectPointToNavigation(Destination, ProjectedDestination))
	{
		Destination = ProjectedDestination.Location;
	}
	Fey->AI_Controller->MoveToLocation(Destination);
}
