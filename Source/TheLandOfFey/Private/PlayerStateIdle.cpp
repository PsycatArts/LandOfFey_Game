// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateIdle.h"


void UPlayerStateIdle::TickState()
{
	Super::TickState();


	
	if (!Player)
		return;

	if (Player->IsAttacking) 
	{
		Player->StateManager->SwitchStateByKey("Attacking");
	}
}

void UPlayerStateIdle::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);
	if (Player->StateManager->bDebug == true)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, TEXT("STATE ENTER: idle"));
	}
	
}

void UPlayerStateIdle::OnExitState()
{
	Super::OnExitState();
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, TEXT("Idle state:ENTER"));
}
