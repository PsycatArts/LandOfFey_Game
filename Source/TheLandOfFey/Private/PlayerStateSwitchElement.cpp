// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerStateSwitchElement.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy/EnemyAI.h"


void UPlayerStateSwitchElement::TickState()
{
	Super::TickState();

}

void UPlayerStateSwitchElement::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

	DisablePlayerMovement();

	if (Player->StateManager->bDebug == true)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, TEXT("STATE ENTER: Switching element"));
	}
	SwitchElement();
}

void UPlayerStateSwitchElement::OnExitState()
{
	Super::OnExitState();
	EnablePlayerMovement();
}

void UPlayerStateSwitchElement::SwitchElement()
{
	//---VFX--
	UWorld* World = GetWorld();
	FVector ParticleLocation = Player->GetActorLocation();
	ParticleLocation.Z -= 90.0f;						//vertical offset (Z-Axis)
	FRotator ParticleRotation(0.f, 0.f, 0.f);

	//SFX
	Player->SwitchElement_SFX();

	//----ANIM---
	float MontageDuration = 0.0f;

	UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance();
	if (AnimInstance && SwitchElement_Montage)
	{
		 MontageDuration = AnimInstance->Montage_Play(SwitchElement_Montage);
	}



	//validation check
	if (Player->ElementSystem->GetCurrentElement() == nullptr)
	{
		//---VFX--
		if (NiagaraParticle_Neutral)
		{
			UNiagaraFunctionLibrary::SpawnSystemAttached(NiagaraParticle_Neutral, Player->GetRootComponent(), NAME_None, ParticleLocation, ParticleRotation, EAttachLocation::KeepWorldPosition, false);
		}

		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT("no element to switch to, switching not possible"));

		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		TimerManager.SetTimer(SwitchResetTimerHandle, this, &UPlayerStateSwitchElement::BackToIdle, MontageDuration, false);
		return;
	}

	// possibly replace by creating switchElem() in ElementBase to override in each element to switch to the other
	if (Player->ElementSystem->GetCurrentElement()->ElementDisplayName == "Light")
	{



		if (Player->ElementSystem->ElementMap.Contains("Dark"))
		{
			//---VFX--
			if (NiagaraParticle_Dark)
			{
				UNiagaraFunctionLibrary::SpawnSystemAttached(NiagaraParticle_Dark, Player->GetRootComponent(), NAME_None, ParticleLocation, ParticleRotation, EAttachLocation::KeepWorldPosition, false);
				
			}
			//---Switch--
			Player->ElementSystem->SwitchElementByKey("Dark");
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT("switching to dark"));
		}
		else 
		{
			//---VFX--
			if (NiagaraParticle_Light)
			{
				UNiagaraFunctionLibrary::SpawnSystemAttached(NiagaraParticle_Light, Player->GetRootComponent(), NAME_None, ParticleLocation, ParticleRotation, EAttachLocation::KeepWorldPosition, false);

			}
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT("PARRY & SWITCH ELEM: NO DARK ELEM FOUND TO SWITCH TO"));
		}
	
	}
	else if (Player->ElementSystem->GetCurrentElement()->ElementDisplayName == "Dark" )		//if current elem is dark , check if light exists, if yes, switch to it
	{
		if (Player->ElementSystem->ElementMap.Contains("Light")) 
		{
			//---VFX--
			if (NiagaraParticle_Light) 
			{
				UNiagaraFunctionLibrary::SpawnSystemAttached(NiagaraParticle_Light, Player->GetRootComponent(), NAME_None, ParticleLocation, ParticleRotation, EAttachLocation::KeepWorldPosition, false);
				
			}
			

			//---Switch--
			Player->ElementSystem->SwitchElementByKey("Light");
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT("switching to Light"));
		}
		//else 
		//{
		//	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT("PARRY & SWITCH ELEM: NO LIGHT ELEM FOUND TO SWITCH TO"));
		//}
		
	}

	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.SetTimer(SwitchResetTimerHandle, this, &UPlayerStateSwitchElement::BackToIdle, MontageDuration, false);

}

void UPlayerStateSwitchElement::BackToIdle()
{
	EnablePlayerMovement();
	Player->StateManager->SwitchStateByKey("Idle");	
}