#include "Enemy/States/EnemyStateCombat.h"
#include "GameFramework/CharacterMovementComponent.h"

void UEnemyStateCombat::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

	ChooseAction();
	Fey->GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void UEnemyStateCombat::TickState()
{
	Super::TickState();
}

void UEnemyStateCombat::OnExitState()
{
	Super::OnExitState();
}

void UEnemyStateCombat::ChooseAction()
{
	if (!Fey->GetIsDead()) 
	{
		if (Fey->ElementSystem->GetCurrentElement() == nullptr)				//if no element, simply attack, else choose attack/ability by random chance
		{
			//neutral behavior
			Fey->StateManager->SwitchStateByKey("Melee");
		}
		else
		{																//possibility of melee or ability
			float randNum = FMath::FRandRange(0.f, 1.f);
			UElementBase* FeyElement = Fey->ElementSystem->GetCurrentElement();

			if (FeyElement->ElementDisplayName == "Light")
			{
				//light behavior
				if (randNum > 0.25f)
				{
					Fey->StateManager->SwitchStateByKey("Ability");
				}
				else
				{
					Fey->StateManager->SwitchStateByKey("Melee");
				}
			}
			else if(FeyElement->ElementDisplayName == "Dark")
			{
				//dark behavior
				if (randNum > 0.35f)
				{
					Fey->StateManager->SwitchStateByKey("Melee");
				}
				else
				{
					Fey->StateManager->SwitchStateByKey("Ability");
				}
			}
		}
	}
	/*else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("ENEMY COMBAT STATE: cant choose action cus DEAD"));
	}*/
}
