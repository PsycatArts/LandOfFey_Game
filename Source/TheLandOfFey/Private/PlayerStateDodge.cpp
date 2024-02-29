// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateDodge.h"

void UPlayerStateDodge::TickState()
{

	Super::TickState();
}

void UPlayerStateDodge::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

	Player->Invincible = true;
	Dodge();
}

void UPlayerStateDodge::OnExitState()
{
	Super::OnExitState();
	Player->Invincible = false;
	Player->IsDodging = false;
}

void UPlayerStateDodge::ReturnToIdle()
{
	Player->StateManager->SwitchStateByKey("Idle");
}

void UPlayerStateDodge::Dodge()
{
	UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance();

	if (!Player->IsDodging && AnimInstance)
	{
		//---SFX---
		Player->Dodge_SFX();

		//---Dodge---
		Player->IsDodging = true;
		float MontageTime;
	

		if (Player->DodgeDirection.Size() > 0)
		{
			//DodgeDirection = DodgeDirection.GetSafeNormal();
			if (Player->IsTargetLocking) 
			{
				//right
				if (Player->DodgeDirection.Y > 0.5)
				{
					MontageTime = AnimInstance->Montage_Play(DodgeRightAnim);
				}
				//left
				else if (Player->DodgeDirection.Y < -0.5)
				{
					MontageTime = AnimInstance->Montage_Play(DodgeLeftAnim);
				}
				//forward
				else if (Player->DodgeDirection.X > 0.5)
				{
					MontageTime = AnimInstance->Montage_Play(DodgeForwardAnim);
				}
				//backward
				else if (Player->DodgeDirection.X < -0.5)
				{
					MontageTime = AnimInstance->Montage_Play(DodgeBackAnim);
				}
			}
			else 
			{
				MontageTime = AnimInstance->Montage_Play(DodgeForwardAnim);
			}
			
			
		}
		else
		{
			if (Player->IsTargetLocking)
			{
				//backward if no direction input
				MontageTime = AnimInstance->Montage_Play(DodgeBackAnim);
			}
			else
			{
				MontageTime = AnimInstance->Montage_Play(DodgeForwardAnim);
			}
			
			
		}
		Player->DodgeDirection = FVector::ZeroVector; // Reset the DodgeDirection
		GetWorld()->GetTimerManager().SetTimer(DodgeTimerHandle, this, &UPlayerStateDodge::ReturnToIdle, MontageTime);
	}
}
