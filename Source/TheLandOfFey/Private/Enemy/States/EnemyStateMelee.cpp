#include "Enemy/States/EnemyStateMelee.h"
#include "Enemy/EnemyAIController.h"
#include "Math/UnrealMathUtility.h"

void UEnemyStateMelee::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

	if (Fey->GetIsDead()) return;

	DeactivateMovement();

	if (Fey->AI_Controller->C_DistanceToPlayer <= AttackRange)  // if player in range, attack.. else chase
	{
		MeleeAttack();
	}
	else
	{
		Fey->StateManager->SwitchStateByKey("Chase");
	}
}

void UEnemyStateMelee::TickState()
{
	Super::TickState();

	//if (Fey->GetIsDead()) return;
	
	if (AttackTimer > 0.0f)										// Decrement timer
	{
		AttackTimer -= GetWorld()->GetDeltaSeconds();
	}
	else if (Fey->AI_Controller->C_DistanceToPlayer <= AttackRange)
	{
		MeleeAttack();
	}
	else
	{
		Fey->StateManager->SwitchStateByKey("Chase");
	}
}

void UEnemyStateMelee::OnExitState()
{
	Super::OnExitState();
	ReactivateMovement();
	GetWorld()->GetTimerManager().ClearTimer(TimerToResetAttackState);
}

FName UEnemyStateMelee::GetAttackSectionName(int32 SectionCount)
{
	FName SectionName;

	const int32 Section{ FMath::RandRange(1, SectionCount) };			//get random section in montage

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


void UEnemyStateMelee::MeleeAttack()
{
	if (AttackTimer > 0.0f)					// If cooldown is active, don't execute an attack
	{
		return;
	}

	Fey->IsAttacking = true;
	Fey->RotateTowardsPlayer();

	if (FeyAnimInstance && Melee_Montage) 
	{
		int32 const SectionCount = Melee_Montage->CompositeSections.Num();

		FName const SectionName = GetAttackSectionName(SectionCount);																//set SectionName
		int32 const SectionIndex = Melee_Montage->GetSectionIndex(SectionName);														//get NAME of current section
		float const SectionLength = Melee_Montage->GetSectionLength(SectionIndex);													//get LENGTH of current section (for timer)

		FeyAnimInstance->Montage_Play(Melee_Montage);
		FeyAnimInstance->Montage_JumpToSection(SectionName, Melee_Montage);

		//---SFX---
		Fey->Melee_SFX();
		
		float randomHurtNum = FMath::FRandRange(0.f, 1.f);													//% possibility to play 
		if (randomHurtNum > 0.5f)
		{
			Fey->Melee_Grunt_SFX();
		}
	

		GetWorld()->GetTimerManager().SetTimer(TimerToResetAttackState, this, &UEnemyStateMelee::BackToCombat, SectionLength);
	}
																																	//reset the cooldown timer at the end of the attack
	AttackCooldown = FMath::FRandRange(0.1f, 1.8f);																					//start the cooldown with a random duration between 0.1f and 2.0f
	AttackTimer = AttackCooldown;
}
