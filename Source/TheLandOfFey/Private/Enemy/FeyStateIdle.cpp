// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/FeyStateIdle.h"
#include "TheLandOfFey/TheLandOfFeyCharacter.h"
#include "Enemy/EnemyAIController.h"
#include "Kismet/GameplayStatics.h"	

void UFeyStateIdle::TickState()
{
	Super::TickState();

	
	ATheLandOfFeyCharacter* Player = Cast<ATheLandOfFeyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Player) return;

	//IF PLAYER DETECTED
	if (!Fey->AI_Controller->bIsPlayerDetected )
	{
		Fey->StateManager->SwitchStateByKey("Patrol");
	}
	else
	{
		//react and go to allert or combat, depending on if the enemy is already allerted or not
		if (!IsAllerted) 
		{
			Fey->StateManager->SwitchStateByKey("Allert");
		}

		Fey->StateManager->SwitchStateByKey("Combat");
	}

}

void UFeyStateIdle::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);
}

void UFeyStateIdle::OnExitState()
{
	Super::OnExitState();
}

