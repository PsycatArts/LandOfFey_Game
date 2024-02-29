// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/FeyStateAllert.h"
#include "Kismet/GameplayStatics.h"	
#include "Enemy/EnemyAIController.h"	
#include "Enemy/EnemyManager.h"	
#include "GameFramework/CharacterMovementComponent.h"

void UFeyStateAllert::TickState()
{
	Super::TickState();
	Fey->GetCharacterMovement()->StopMovementImmediately();
	Fey->GetCharacterMovement()->DisableMovement();

	if (Fey->GetIsDead())
	{
		Fey->StateManager->SwitchStateByKey("Death");
		return;
	}
	
}

void UFeyStateAllert::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

	Fey->GetCharacterMovement()->StopMovementImmediately();
	Fey->GetCharacterMovement()->DisableMovement();
	IsAllerted = true;

	Allerted();
}

void UFeyStateAllert::OnExitState()
{
	Super::OnExitState();
	Fey->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

void UFeyStateAllert::Allerted()
{
	
	Fey->RotateTowardsPlayer();
	UAnimInstance* AnimInstance = Fey->GetMesh()->GetAnimInstance();

	if (AnimInstance && Allerted_Montage)
	{
		float MontageDuration = AnimInstance->Montage_Play(Allerted_Montage);

		Fey->EnemyManager->AddAllertedEnemy(Fey);

		GetWorld()->GetTimerManager().SetTimer(AllertedTimerHandle, this, &UFeyStateAllert::CheckSituation, MontageDuration);
	}
}


void UFeyStateAllert::StartCombat()
{
	Fey->StateManager->SwitchStateByKey("Combat");
}

//function to check for situation, if 2> enemies in Mangager list, observe, else combat
void UFeyStateAllert::CheckSituation()
{
	if (Fey->EnemyManager->AttackingEnemies.Num() < 2)
	{
		Fey->EnemyManager->AttackingEnemies.Add(Fey);
		Fey->StateManager->SwitchStateByKey("Combat");
	}
	else
	{
		Fey->StateManager->SwitchStateByKey("Observe");
	}
}

