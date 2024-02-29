#include "Enemy/States/EnemyStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"


void UEnemyStateBase::OnEnterState(AActor* OwnerRef)
{
	Super::OnEnterState(OwnerRef);

	if (!Fey)
	{
		Fey = Cast<AFeyAI>(OwnerRef);
	}
	if (!FeyAnimInstance) 
	{
		UAnimInstance* AnimInstance = Fey->GetMesh()->GetAnimInstance();
		FeyAnimInstance = AnimInstance;
	}

	if (!Player) 
	{
		Player = Cast<ATheLandOfFeyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}
	IsAlerted = false;
}

void UEnemyStateBase::OnExitState()
{
	Super::OnExitState();
}

void UEnemyStateBase::DeactivateMovement()
{
	Fey->GetCharacterMovement()->DisableMovement();
}

void UEnemyStateBase::ReactivateMovement()
{
	Fey->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

void UEnemyStateBase::BackToCombat()
{
	Fey->StateManager->SwitchStateByKey("Combat");
}
