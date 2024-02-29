#include "Enemy/States/EnemyStateAlert.h"

void UEnemyStateAlert::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

	DeactivateMovement();
	IsAlerted = true;

	Alerted();
}

void UEnemyStateAlert::TickState()
{
	Super::TickState();
}

void UEnemyStateAlert::OnExitState()
{
	Super::OnExitState();

	ReactivateMovement();
	GetWorld()->GetTimerManager().ClearTimer(AlertTimerHandle);
}


void UEnemyStateAlert::Alerted()											//play alert animation.. then check
{
	Fey->RotateTowardsPlayer();
	if (FeyAnimInstance && Alert_Montage)
	{
		Fey->Alert_SFX();

		float MontageDuration = FeyAnimInstance->Montage_Play(Alert_Montage);

		Fey->EnemyManager->AddAllertedEnemy(Fey);

		GetWorld()->GetTimerManager().SetTimer(AlertTimerHandle, this, &UEnemyStateAlert::CheckSituation, MontageDuration);
	}
}


void UEnemyStateAlert::CheckSituation()																						//check for combat or observe
{
	if (Fey->EnemyManager->AttackingEnemies.Num() < 2)																		//if less than two enemies attacking..
	{
		Fey->EnemyManager->AttackingEnemies.Add(Fey);																		//add this enemy to attacker list
		Fey->StateManager->SwitchStateByKey("Combat");
	}
	else
	{
		Fey->StateManager->SwitchStateByKey("Observe");
	}
}
