// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateStun.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerStateStun::TickState()
{
	Super::TickState();


	if(Player->Stunned==false)
	{
		Player->StateManager->SwitchStateByKey("Idle");
	}
}

void UPlayerStateStun::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);
	if (Player->StateManager->bDebug == true)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, TEXT("STATE ENTER: Stun"));
	}


	Player->Stunned = true;


	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	DisablePlayerMovement();
	//Player->DisableInput(PlayerController);

	UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance();
	if (Stun_Montage) {
		AnimInstance->Montage_Play(Stun_Montage);
	}
	GetWorld()->GetTimerManager().SetTimer(StunTimer, this, &UPlayerStateStun::ResettingStun, Stun_Time);

}

void UPlayerStateStun::ResettingStun()
{

	Player->Stunned = false;
}

void UPlayerStateStun::OnExitState()
{
	Super::OnExitState();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	//Player->EnableInput(PlayerController);
	EnablePlayerMovement();

}


