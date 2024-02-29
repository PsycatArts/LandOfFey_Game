// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateDeath.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Engine/LevelScriptActor.h>

void UPlayerStateDeath::TickState()
{
	Super::TickState();
}

void UPlayerStateDeath::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);
	//if (Player->StateManager->bDebug == true)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, TEXT("STATE ENTER: death"));
	//}
	//
	//if (!Player)
	//	return;

	//Player->Health = 0.f;
	//Player->IsDead = true;

	//UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance();
	//if (Death_Montage) 
	//{
	//	AnimInstance->Montage_Play(Death_Montage);
	//}

	//Player->GetCharacterMovement()->DisableMovement();
	//Player->GetCharacterMovement()->bOrientRotationToMovement = false;
	//Player->GetCharacterMovement()->bUseControllerDesiredRotation = false;

	//APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	//if (PlayerController) 
	//{
	//	Player->DisableInput(PlayerController);

	//	//allow mouse
	//	PlayerController->bShowMouseCursor = true;
	//	PlayerController->bEnableClickEvents = true;
	//	PlayerController->bEnableMouseOverEvents = true;

	//	
	//}

	//death sound & vfx

}

void UPlayerStateDeath::OnExitState()
{
	Super::OnExitState();
}
