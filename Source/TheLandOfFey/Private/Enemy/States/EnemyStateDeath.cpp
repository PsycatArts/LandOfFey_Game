#include "Enemy/States/EnemyStateDeath.h"
#include "Components/CapsuleComponent.h"

void UEnemyStateDeath::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

	Death();
}

void UEnemyStateDeath::TickState()
{
	Super::TickState();
}

void UEnemyStateDeath::OnExitState()
{
	Super::OnExitState();
}

void UEnemyStateDeath::Death()
{
	Fey->IsDead = true;

	Fey->Health = 0.f;
	Fey->EnemyManager->RemoveAllertedEnemy(Fey);

	DeactivateMovement();

	UCapsuleComponent* CapsuleComponent = Fey->GetCapsuleComponent();
	if (CapsuleComponent)
	{
		CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	//---SFX---
	Fey->Death_SFX();

	//---ANIM--
	if (FeyAnimInstance && Death_Montage)
	{
		FeyAnimInstance->Montage_Play(Death_Montage);
	}
	//---VFX---
	Fey->Death_Fade();
}
