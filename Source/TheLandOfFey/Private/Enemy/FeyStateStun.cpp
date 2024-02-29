// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/FeyStateStun.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"

void UFeyStateStun::TickState()
{
	Super::TickState();

	Fey->GetCharacterMovement()->StopMovementImmediately();
	Fey->GetCharacterMovement()->DisableMovement();
}
void UFeyStateStun::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

	//Fey->IsStunned = true;

	UAnimInstance* AnimInstance = Fey->GetMesh()->GetAnimInstance();
	if (AnimInstance && Stun_Montage)
	{
		AnimInstance->Montage_Play(Stun_Montage);
		GetWorld()->GetTimerManager().SetTimer(StunTimer, this, &UFeyStateStun::BackToCombat, StunDuration/*+ 1.f */);
	}
}

void UFeyStateStun::BackToCombat() 
{
	Fey->StateManager->SwitchStateByKey("Combat");

}
void UFeyStateStun::OnExitState()
{
	Super::OnExitState();

	//Fey->Parried = false;

	Fey->GetCharacterMovement()->SetMovementMode(MOVE_Walking);

}
