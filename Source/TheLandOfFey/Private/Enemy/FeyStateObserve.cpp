// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/FeyStateObserve.h"
#include "Kismet/GameplayStatics.h"	
#include "Enemy/EnemyAIController.h"	
#include "TheLandOfFey/TheLandOfFeyCharacter.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UFeyStateObserve::TickState()
{
	Super::TickState();

//	Fey->GetCharacterMovement()->StopMovementImmediately();
//	Fey->GetCharacterMovement()->DisableMovement();


}

void UFeyStateObserve::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

	Fey->GetCharacterMovement()->StopMovementImmediately();
	Fey->GetCharacterMovement()->DisableMovement();

	Observing();
}

void UFeyStateObserve::OnExitState()
{
	Super::OnExitState();
	Fey->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

void UFeyStateObserve::Observing()
{
	Fey->GetCharacterMovement()->StopMovementImmediately();
	Fey->GetCharacterMovement()->DisableMovement();

	UAnimInstance* AnimInstance = Fey->GetMesh()->GetAnimInstance();

	if (AnimInstance && Observing_Montage)
	{
		float MontageDuration = AnimInstance->Montage_Play(Observing_Montage);
		GetWorld()->GetTimerManager().SetTimer(CheckingTimerHandle, this, &UFeyStateObserve::CheckSituation, MontageDuration);
		//GetWorld()->GetTimerManager().SetTimer(AllertedTimerHandle, this, &UFeyStateObserve::StartCombat, MontageDuration);
	}
}

void UFeyStateObserve::MoveAwayFromPlayer()
{
	Fey->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
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

//void UFeyStateObserve::StartCombat()
//{
//	Fey->StateManager->SwitchStateByKey("Combat");
//}

void UFeyStateObserve::CheckSituation()
{
	if (Fey->EnemyManager->AllertedEnemies.Num() > 2)
	{
		//if player too close..
		if (Fey->AI_Controller->C_DistanceToPlayer <= ObserveDistance) 
		{
			//create distance
			MoveAwayFromPlayer();
			GetWorld()->GetTimerManager().SetTimer(CheckingTimerHandle, this, &UFeyStateObserve::Observing, 2.f);
		}
		else 
		{
			Observing();
		}
		

		//Fey->StateManager->SwitchStateByKey("Observe");

		
	}
	else
	{
		Fey->StateManager->SwitchStateByKey("Combat");
	}
	//if 2 feys are still in combat with player, keep on observing... otherwise StartCombat
}
