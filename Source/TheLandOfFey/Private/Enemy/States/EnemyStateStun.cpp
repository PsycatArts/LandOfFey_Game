#include "Enemy/States/EnemyStateStun.h"

void UEnemyStateStun::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

	DeactivateMovement();
	Stun();
}

void UEnemyStateStun::TickState()
{
	Super::TickState();
}

void UEnemyStateStun::OnExitState()
{
	Super::OnExitState();

	ReactivateMovement();
	GetWorld()->GetTimerManager().ClearTimer(StunTimer);
}

void UEnemyStateStun::Stun()
{
	if (FeyAnimInstance && Stun_Montage)
	{
		FeyAnimInstance->Montage_Play(Stun_Montage);
		GetWorld()->GetTimerManager().SetTimer(StunTimer, this, &UEnemyStateStun::BackToCombat, StunDuration);
	}
}
