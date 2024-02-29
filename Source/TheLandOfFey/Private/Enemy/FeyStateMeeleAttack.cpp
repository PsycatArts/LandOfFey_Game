// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/FeyStateMeeleAttack.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Enemy/EnemyAIController.h"
#include "Animation/AnimInstance.h"

void UFeyStateMeeleAttack::TickState()
{
	Super::TickState();
	
	Fey->GetCharacterMovement()->StopMovementImmediately();
	Fey->GetCharacterMovement()->DisableMovement();

	if (Fey->IsHurting)
	{
		Fey->StateManager->SwitchStateByKey("Hurt");
	}

}

void UFeyStateMeeleAttack::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

	if (!Fey->IsHurting) 
	{
		Fey->GetCharacterMovement()->DisableMovement();
		


		if (Fey->AI_Controller->C_DistanceToPlayer <= RangeToAttack)
		{
			MeeleAttack();
		}
		else
		{
			// IS ATTACKING CHECK HERE was probably solution to movement while attacking issue..
			if (!Fey->IsAttacking) 
			{			
				Fey->StateManager->SwitchStateByKey("Chase");
			}

		}
	}
	else 
	{
		Fey->StateManager->SwitchStateByKey("Combat");
	}
	
	
}
//GET RANDOM ATTACK TO PLAY (get section name)
FName UFeyStateMeeleAttack::GetAttackSectionName(int32 SectionCount)
{
	FName SectionName;

	//get random section in montage
	const int32 Section{ FMath::RandRange(1, SectionCount) };

	switch (Section)
	{
	case 1:
		SectionName = FName("Attack1");
		break;
	case 2:
		SectionName = FName("Attack2");
		break;
	case 3:
		SectionName = FName("Attack3");
		break;
	}

	return SectionName;
}

void UFeyStateMeeleAttack::ReturnToCombat() 
{
	Fey->StateManager->SwitchStateByKey("Combat");
}

void UFeyStateMeeleAttack::MeeleAttack()
{
	Fey->IsAttacking = true;
	Fey->RotateTowardsPlayer();

	UAnimInstance* AnimInstance = Fey->GetMesh()->GetAnimInstance();

	//play a meele anim
	if (AnimInstance && MeeleAttack_Montage)
	{
		int32 const SectionCount = MeeleAttack_Montage->CompositeSections.Num();

		FName const SectionName = GetAttackSectionName(SectionCount);									//set SectionName
		int32 const SectionIndex = MeeleAttack_Montage->GetSectionIndex(SectionName);					//get NAME of current section
		float const SectionLength = MeeleAttack_Montage->GetSectionLength(SectionIndex);				//get LENGTH of current section (for timer)
		// Play montage section
		AnimInstance->Montage_Play(MeeleAttack_Montage);
		AnimInstance->Montage_JumpToSection(SectionName, MeeleAttack_Montage);

		//back to combat state after anim
		GetWorld()->GetTimerManager().SetTimer(TimerToResetAttackState, this, &UFeyStateMeeleAttack::ReturnToCombat, SectionLength/*+ 1.f */);
	}
}


void UFeyStateMeeleAttack::OnExitState()
{
	Super::OnExitState();
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT("FEY STATE: exit Meeleattack"));
	Fey->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	Fey->IsAttacking = false;
}
