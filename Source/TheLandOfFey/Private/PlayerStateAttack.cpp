// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerStateAttack.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"



void UPlayerStateAttack::TickState()
{
	Super::TickState();

	if (!Player)
		return;
	
	if (Player->IsAttacking==false)
	{
		EnablePlayerMovement();
		Player->StateManager->SwitchStateByKey("Idle");
	}
}

void UPlayerStateAttack::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);
	if (Player->StateManager->bDebug == true)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, TEXT("STATE ENTER: attack"));
	}

	DisablePlayerMovement();
	Attacking();
}

void UPlayerStateAttack::OnExitState()
{
	Super::OnExitState();

	EnablePlayerMovement();
	Player->IsAttacking=false;
}


void UPlayerStateAttack::Attacking()
{
	if (!Player) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Attack state:no player ref round"));
		return;
	}

	UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance();

	if ( !Player->IsAttacking && bAllowNextAttack)
	{
		//attack into direction which camera is facing
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController)
		{
			FRotator CameraRotation = PlayerController->GetControlRotation();
			FRotator PlayerRotation = Player->GetActorRotation();

			Player->SetActorRotation(FRotator(PlayerRotation.Pitch, CameraRotation.Yaw, PlayerRotation.Roll));
		}


		bAllowNextAttack = false;
		//delay before allowing next attack
		FTimerHandle TH_AllowNextAttack;
		GetWorld()->GetTimerManager().SetTimer(TH_AllowNextAttack, [this]() { bAllowNextAttack = true; }, 0.4f, false);

		//SFX
		Player->Melee_SFX();

		switch (ComboAttack_Num)
		{
		case 0:
			AnimInstance->Montage_Play(MainAttack_1_Montage);
			Player->IsAttacking = true;
			ComboAttack_Num++;
			break;
		case 1:
			AnimInstance->Montage_Play(MainAttack_2_Montage);
			Player->IsAttacking = true;
			ComboAttack_Num++;
			break;
		case 2:
			AnimInstance->Montage_Play(MainAttack_3_Montage);
			Player->IsAttacking = true;
			ComboAttack_Num++;
			ComboAttack_Num = 0;
			break;
		default:
			ComboAttack_Num = 0;
		}
		GetWorld()->GetTimerManager().SetTimer(ComboResetTimer, this, &UPlayerStateAttack::ResetMainAttack, ComboResetTime, false);
	}
}


void UPlayerStateAttack::ResetMainAttack()
{
	if (!Player->IsAttacking)
	{
		ComboAttack_Num = 0;
	}
	// Clear the timer
	GetWorld()->GetTimerManager().ClearTimer(ComboResetTimer);
}

//void UPlayerStateAttack::MainAttack_End()
//{
//	Player->IsAttacking = false;
//}

