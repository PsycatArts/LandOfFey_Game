// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerStateAbilityA.h"
#include "ElementBase.h"
#include "Animation/AnimInstance.h"


void UPlayerStateAbilityA::TickState()
{
	Super::TickState();

}

void UPlayerStateAbilityA::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);
	if (Player->StateManager->bDebug == true)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, TEXT("STATE ENTER: AbilityA"));
	}
	//DisablePlayerMovement();

	UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance();

	if (AnimInstance && Ability_A_Montage)
	{
		float MontageDuration = AnimInstance->Montage_Play(Ability_A_Montage);

		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		TimerManager.SetTimer(AbilityResetTimerHandle, this, &UPlayerStateAbilityA::BackToIdle, MontageDuration, false);
	}




	////check for element
	//UElementBase* AnyElement = Player->ElementSystem->GetCurrentElement();

	//if (!AnyElement)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange, TEXT("No element active, can not do ability attack"));
	//	BackToIdle();
	//	return;
	//}

	//if (AnyElement->ElementDisplayName == "Light")
	//{
	//	//crystal
	//	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange, TEXT("LIGHT ability used"));
	//	//UseAbilityA();
	//	//Player->Slope();
	//}
	//else if (AnyElement->ElementDisplayName == "Dark")
	//{
	//	//dark
	//	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange, TEXT("DARK ability used"));
	//	//BackToIdle();
	//	//Player->Dash();
	//}
	
}

void UPlayerStateAbilityA::OnExitState()
{
	Super::OnExitState();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	//Player->EnableInput(PlayerController);
	EnablePlayerMovement();
}

void UPlayerStateAbilityA::UseAbilityA()
{



	SpawnObject();
	
	//REACTIVATE LATER if modularity of element related is wanted

	//UElementBase* AnyElement = Player->ElementSystem->GetCurrentElement();
	//if (!AnyElement)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange, TEXT("No element active, can not do ability attack"));
	//	return;
	//}
	////calls ability logic
	//AnyElement->AbilityAttack(Player);

	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.SetTimer(AbilityResetTimerHandle, this, &UPlayerStateAbilityA::BackToIdle, AbilityDuration, false);

}

//replaced by BP spawn logic
void UPlayerStateAbilityA::SpawnObject()
{
	////if slope exists, destroy previous
	//DestroyObject();

	////spawn slope
	//FVector SpawnLocation = Player->GetActorLocation() + Player->GetActorForwardVector() * 100.0f;
	//FRotator SpawnRotation = Player ->GetActorRotation();

	//SpawnedSlopeActor = GetWorld()->SpawnActor<AActor>(SlopeToSpawn, SpawnLocation, SpawnRotation);

	////to destroy slope after x secs
	//FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	//TimerManager.SetTimer(SlopeTimerHandle, this, &UPlayerStateAbilityA::DestroyObject, DestroySlopeTime, false);
}

void UPlayerStateAbilityA::DestroyObject()
{
	////destroy
	//if (SpawnedSlopeActor != nullptr)
	//{
	//	//vfx  & SFX

	//	SpawnedSlopeActor->Destroy();
	//	SpawnedSlopeActor = nullptr; // reset SpawnedSlopeActor
	//}
}

void UPlayerStateAbilityA::BackToIdle()
{
	Player->StateManager->SwitchStateByKey("Idle");
	
}
