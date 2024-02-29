// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/FeyStateCombat.h"
#include "Enemy/EnemyAIController.h"
#include "Kismet/GameplayStatics.h"	
#include "Engine/World.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "Kismet/GameplayStatics.h"	
#include "Math/UnrealMathUtility.h"
#include "TheLandOfFey/TheLandOfFeyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UFeyStateCombat::TickState()
{
	Super::TickState();

	if (Fey->GetIsDead()) 
	{
		Fey->StateManager->SwitchStateByKey("Death");
		return;
	}
	else if (!Fey->IsHurting && !Fey->GetIsDead()) 
	{
		DecideNextAction();
	}

}

void UFeyStateCombat::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

	Fey->GetCharacterMovement()->MaxWalkSpeed = 600.f;	
}

void UFeyStateCombat::OnExitState()
{
	Super::OnExitState();
}

void UFeyStateCombat::DecideNextAction()
{
	ATheLandOfFeyCharacter* Player = Cast<ATheLandOfFeyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Player) return;

	float DistanceToPlayer = FVector::Dist(Fey->GetActorLocation(), Player->GetActorLocation());

	//check if we CAN attack again..
	if (GetWorld()->GetTimerManager().IsTimerActive(AttackTimer))
	{
		//wait for timer to expire before attacking again
		return;
	}
	//Attack FCT AFTER x SECONDS
	GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &UFeyStateCombat::SwitchToAttack, 0.3f);
}


//probably HERE add the "if not hurt/stunned" so he doesnt attack when hurting
void UFeyStateCombat::SwitchToAttack()
{
	if (!Fey->IsHurting ) 
	{
		//if no element, simply attack, else choose attack/ability by random chance
		if (Fey->ElementSystem->GetCurrentElement() == nullptr)
		{
			Fey->StateManager->SwitchStateByKey("MeeleAttack");
		}
		else
		{
			//CHOOSE RANDOM ATTACK
			float randNum = FMath::FRandRange(0.f, 1.f);

			//50% chance of choosing one of those
			if (randNum > 0.35f)
			{
				Fey->StateManager->SwitchStateByKey("MeeleAttack");
			}
			else //35% chance to take ability
			{
				Fey->StateManager->SwitchStateByKey("AbilityA");
			}
		}
	}
}



//not used rn
void UFeyStateCombat::CircleAroundPlayer(float Distance, float CircleSpeed)
{

	////works but looks very weird and snappy
	//if (!Fey->IsDead)
	//{
	//	// Get the player character
	//	ATheLandOfFeyCharacter* Player = Cast<ATheLandOfFeyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//	if (!Player)
	//		return;

	//	// Get the direction vector to the player
	//	FVector Direction = Player->GetActorLocation() - Fey->GetActorLocation();
	//	Direction.Normalize();

	//	// Calculate the position for the enemy to move to
	//	FVector CirclingDirection = FVector(-Direction.Y, Direction.X, 0.f); // Rotate the direction vector 90 degrees

	//	// Adjust the circling distance by moving the enemy towards or away from the player
	//	float CurrentDistance = FVector::Distance(Player->GetActorLocation(),Fey->GetActorLocation() );
	//	float DistanceDifference = CurrentDistance - Distance;
	//	FVector AdjustedDirection = Direction * DistanceDifference * CircleSpeed;

	//	// Update the enemy's position using AddMovementInput
	//	FVector MovementDirection = AdjustedDirection + CirclingDirection * CircleSpeed;
	//	Fey->AddMovementInput(MovementDirection);

	//	// Rotate the enemy towards the player
	//	Fey->RotateTowardsPlayer();
	//}
	//
}
