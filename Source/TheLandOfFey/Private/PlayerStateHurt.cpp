// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateHurt.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void UPlayerStateHurt::TickState()
{
	Super::TickState();

	if (!Player)
		return;

	//if (Player->Health <= 0 && !Player->IsDead) 
	//{
	//	Player->StateManager->SwitchStateByKey("Death");
	//}


	if (Player->IsHurting == false)
	{
		Player->StateManager->SwitchStateByKey("Idle");
	}
	
}

void UPlayerStateHurt::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

	DisablePlayerMovement();

	Player->IsHurting = true;
	Player->Invincible = true;
	Player->IsAttacking = false;


	UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance();
	if (Hurt_Montage) {
		AnimInstance->Montage_Play(Hurt_Montage);
	}
	GetWorld()->GetTimerManager().SetTimer(HurtTimer, this, &UPlayerStateHurt::ReturnToIdle, Hurt_Time);

}

void UPlayerStateHurt::OnExitState()
{
	Super::OnExitState();
	EnablePlayerMovement();
}

void UPlayerStateHurt::ReturnToIdle()
{
	//GetWorld()->GetTimerManager().SetTimer(InvincibilityTimer, this, &UPlayerStateHurt::Invincibility, i_Frames_Time);
	Player->IsHurting = false;
	Player->Invincible = false;
	//Player->StateManager->SwitchStateByKey("Idle");
}

void UPlayerStateHurt::Invincibility()
{
	//Player->Invincible = false;
}
