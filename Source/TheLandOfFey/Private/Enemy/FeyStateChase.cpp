// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/FeyStateChase.h"
#include "Enemy/EnemyAIController.h"
#include "TheLandOfFey/TheLandOfFeyCharacter.h"
#include "Kismet/GameplayStatics.h"	

void UFeyStateChase::TickState()
{
	Super::TickState();

	ATheLandOfFeyCharacter* Player = Cast<ATheLandOfFeyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Player )
	{
		return;
	}
	if (Fey->GetIsDead()) 
	{
		return;
	}



	if (Fey->AI_Controller->C_DistanceToPlayer <= RangeToAttack) 
	{
		Fey->StateManager->SwitchStateByKey("Combat");
	}
	else 
	{
		// IS ATTACKING CHECK HERE was probably solution to movement while attacking issue..
		if (!Fey->IsHurting && !Fey->IsAttacking) 
		{
			Fey->AI_Controller->MoveToLocation(Player->GetActorLocation());
		}
		

	}
}

void UFeyStateChase::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

}

void UFeyStateChase::OnExitState()
{
	Super::OnExitState();
}
