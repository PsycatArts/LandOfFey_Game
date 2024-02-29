// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/FeyStateAbilityA.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Enemy/EnemyAIController.h"
#include "TheLandOfFey/TheLandOfFeyCharacter.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "Kismet/GameplayStatics.h"	
#include "GameFramework/CharacterMovementComponent.h"
#include "ElementBase.h"

//this state still contains logic to execute the Light or Darkability depending on the enemies element
void UFeyStateAbilityA::TickState()
{
	Super::TickState();
}

void UFeyStateAbilityA::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);
	UElementBase* AnyElement = Fey->ElementSystem->GetCurrentElement();

	if (!AnyElement) return;

	ATheLandOfFeyCharacter* Player = Cast<ATheLandOfFeyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Player) return;

	float DistanceToPlayer = FVector::Dist(Fey->GetActorLocation(), Player->GetActorLocation());

	//light ability
	if (AnyElement->ElementDisplayName=="Light") 
	{
		if (DistanceToPlayer < MinProjectileDistance/*Fey->AI_Controller->C_DistanceToPlayer <= MinProjectileDistance*/)
		{
			MoveAwayFromPlayer();
		}

		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		//spawn projectile
		TimerManager.SetTimer(MoveAwayTimer, this, &UFeyStateAbilityA::UseProjectile, 1.f, false);
	}
	//dark ability
	else if (AnyElement->ElementDisplayName == "Dark") 
	{
		UseAbility();
	}
}

void UFeyStateAbilityA::OnExitState()
{
	Super::OnExitState();
}

//FOG CLOUD
void UFeyStateAbilityA::UseAbility()
{
	
	//play animation montage
	UAnimInstance* AnimInstance = Fey->GetMesh()->GetAnimInstance();

	if (FogCloud_Ability_Montage)
	{
		AnimInstance->Montage_Play(FogCloud_Ability_Montage);

	}
	Fey->RotateTowardsPlayer();
	//if Fog exists, destroy previous
	DestroyObject();


	
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	TimerManager.SetTimer(FogSpawnTimerHandle, this, &UFeyStateAbilityA::SpawnFog, ProjectileSpawnAfter, false);
	TimerManager.SetTimer(FogTimerHandle, this, &UFeyStateAbilityA::DestroyObject, DestroyFogTime, false);				//destroy fog
	TimerManager.SetTimer(AbilityResetTimerHandle, this, &UFeyStateAbilityA::BackToCombat, AbilityDuration, false);		//exit state

}

void UFeyStateAbilityA::SpawnFog()
{
	//spawn  fog
	FVector SpawnLocation = Fey->GetActorLocation() + Fey->GetActorForwardVector() * 200.0f;
	FRotator SpawnRotation = Fey->GetActorRotation();

	SpawnedFogActor = GetWorld()->SpawnActor<AActor>(FogToSpawn, SpawnLocation, SpawnRotation);

}

//CRYSTAL PROJECTILE 
void UFeyStateAbilityA::UseProjectile()
{
	UAnimInstance* AnimInstance = Fey->GetMesh()->GetAnimInstance();
	if (FogCloud_Ability_Montage)
	{
		AnimInstance->Montage_Play(FogCloud_Ability_Montage);

	}
	Fey->RotateTowardsPlayer();
	//if projectile exists, destroy previous
	DestroyObject();

	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	//spawn obj
	TimerManager.SetTimer(CrystalTimerHandle, this, &UFeyStateAbilityA::SpawnProjectile, ProjectileSpawnAfter, false);
	//Destroy obj
	TimerManager.SetTimer(FogTimerHandle, this, &UFeyStateAbilityA::DestroyObject, DestroyProjectileTime, false);				//destroy fog
	//back to idle
	TimerManager.SetTimer(AbilityResetTimerHandle, this, &UFeyStateAbilityA::BackToCombat, AbilityDuration, false);				//exit state
}


void UFeyStateAbilityA::SpawnProjectile()
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



void UFeyStateAbilityA::BackToCombat()
{
	Fey->StateManager->SwitchStateByKey("Combat");

}

void UFeyStateAbilityA::DestroyObject()
{
	//destroy
	UElementBase* FeyElement = Fey->ElementSystem->GetCurrentElement();

	//light
	if (FeyElement->ElementDisplayName == "Light")
	{
		if (SpawnedProjectileActor == nullptr)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange, TEXT("No crystal to destroy exists"));
			return;
		}
		else 
		{
			//vfx  & SFX
			SpawnedProjectileActor->Destroy();
			SpawnedProjectileActor = nullptr;
		}

	}
	else if (FeyElement->ElementDisplayName == "Dark") 
	{
		if (SpawnedFogActor == nullptr)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange, TEXT("No fog to destroy exists"));
			return;
		}
		else
		{
			//vfx  & SFX
			SpawnedFogActor->Destroy();
			SpawnedFogActor = nullptr;
		}
	}
	else 
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange, TEXT("No element assigned, no object to destroy"));
		return;
	}
}

void UFeyStateAbilityA::MoveAwayFromPlayer()
{
	ATheLandOfFeyCharacter* Player = Cast<ATheLandOfFeyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Player)
		return;

	//calculate direction
	FVector Direction = Fey->GetActorLocation() - Player->GetActorLocation();
	Direction.Normalize();

	FVector Destination = Fey->GetActorLocation() + Direction * 400;

	//ensure navmesh projection destination is on navmesh
	FNavLocation ProjectedDestination;

	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(Fey->GetWorld());
	if (NavSystem && NavSystem->ProjectPointToNavigation(Destination, ProjectedDestination))
	{
		Destination = ProjectedDestination.Location;
	}
	//move AI
	Fey->AI_Controller->MoveToLocation(Destination);
}
