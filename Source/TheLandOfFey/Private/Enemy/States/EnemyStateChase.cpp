#include "Enemy/States/EnemyStateChase.h"
#include "Enemy/EnemyAIController.h"

void UEnemyStateChase::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

	
}

void UEnemyStateChase::TickState()
{
	Super::TickState();

	Chase();
}

void UEnemyStateChase::OnExitState()
{
	Super::OnExitState();
}

void UEnemyStateChase::Chase()
{
	if (Fey->GetIsDead()) return;

	if (Fey->AI_Controller->C_DistanceToPlayer <= AttackRange)					//if player in range to attack, enter combat.. else chase player
	{
		Fey->StateManager->SwitchStateByKey("Combat");
	}
	else
	{
		Fey->AI_Controller->MoveToLocation(Player->GetActorLocation());
	}
}
