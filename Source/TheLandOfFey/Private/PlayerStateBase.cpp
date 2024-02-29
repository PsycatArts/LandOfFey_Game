// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "TheLandOfFey/TheLandOfFeyCharacter.h"
#include "GameFramework/PlayerController.h"
//#include "MyPlayerHud.h"
//#include "Blueprint/UserWidget.h"


void UPlayerStateBase::OnEnterState(AActor* OwnerRef)
{
	Super::OnEnterState(OwnerRef);

	if (!Player) 
	{
		Player = Cast<ATheLandOfFeyCharacter>(OwnerRef);
	}
	
}

void UPlayerStateBase::OnExitState()
{
	Super::OnExitState();

}

void UPlayerStateBase::Attacking()
{

}

void UPlayerStateBase::DisablePlayerMovement()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->SetIgnoreMoveInput(true);
	}
}

void UPlayerStateBase::EnablePlayerMovement()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->SetIgnoreMoveInput(false);
	}
}
