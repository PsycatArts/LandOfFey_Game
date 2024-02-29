// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/FeyStatePatrol.h"
#include "Enemy/EnemyAIController.h"
#include "Kismet/GameplayStatics.h"	
#include "Engine/World.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "Kismet/GameplayStatics.h"	
#include "GameFramework/CharacterMovementComponent.h"

void UFeyStatePatrol::TickState()
{
	Super::TickState();

	//if player pawn not in sight
	if(!Fey->AI_Controller->bIsPlayerDetected)
	{
		//PATROLLING AFTER X SECS
		if (GetWorld()->GetTimerManager().IsTimerActive(PatrolTimer))
		{
			//wait for timer to expire before moving to next point
			return;
		}
		GetWorld()->GetTimerManager().SetTimer(PatrolTimer, this, &UFeyStatePatrol::Patrolling, 3.5f);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(PatrolTimer);
		Fey->StateManager->SwitchStateByKey("Allert");
	}
}

void UFeyStatePatrol::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

	Fey->GetCharacterMovement()->MaxWalkSpeed = 300.f;
}

void UFeyStatePatrol::OnExitState()
{
	Super::OnExitState();
}

void UFeyStatePatrol::Patrolling()
{
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(Fey->GetWorld());
	FNavLocation RandomPoint;
	if (NavSys->GetRandomPointInNavigableRadius(Fey->GetActorLocation(), Patrol_Range, RandomPoint))
	{
		// Move AI
		if (Fey->AI_Controller)
		{
			Fey->AI_Controller->MoveToLocation(RandomPoint.Location);
		}
	}
}

void UFeyStatePatrol::StartCombat()
{
	Fey->StateManager->SwitchStateByKey("Combat");
}
