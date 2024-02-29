#include "Enemy/States/EnemyStateObserve.h"
#include "Enemy/EnemyAIController.h"
#include "NavigationSystem.h"

void UEnemyStateObserve::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

	Observe();
}

void UEnemyStateObserve::TickState()
{
	Super::TickState();
}

void UEnemyStateObserve::OnExitState()
{
	Super::OnExitState();

	GetWorld()->GetTimerManager().ClearTimer(CheckingTimerHandle);
}

void UEnemyStateObserve::Observe()
{
	Fey->RotateTowardsPlayer();

	DeactivateMovement();

	if (FeyAnimInstance && Observe_Montage)
	{
		float MontageDuration = FeyAnimInstance->Montage_Play(Observe_Montage);
		GetWorld()->GetTimerManager().SetTimer(CheckingTimerHandle, this, &UEnemyStateObserve::CheckSituation, MontageDuration);
	}
}

void UEnemyStateObserve::CheckSituation()
{
	if (Fey->EnemyManager->AllertedEnemies.Num() > 2)																	//if more than 2 enemies allerted.. enemy still in observe
	{
		if (Fey->AI_Controller->C_DistanceToPlayer <= ObserveDistance)													//check if player too close and create distance 
		{
			CreateDistance();
			GetWorld()->GetTimerManager().SetTimer(CheckingTimerHandle, this, &UEnemyStateObserve::Observe, 3.f);
		}
		else
		{
			Observe();																									//play observe anim again
		}
	}																													//if less than 2 enemies allerted, enter combat
	else
	{
		Fey->StateManager->SwitchStateByKey("Combat");
	}
}

void UEnemyStateObserve::CreateDistance()
{
	if (!Player) return;

	ReactivateMovement();

	FVector Direction = Fey->GetActorLocation() - Player->GetActorLocation();				
	Direction.Normalize();

	FVector Destination = Fey->GetActorLocation() + Direction * 400;

	FNavLocation ProjectedDestination;

	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(Fey->GetWorld());
	if (NavSystem && NavSystem->ProjectPointToNavigation(Destination, ProjectedDestination))
	{
		Destination = ProjectedDestination.Location;
		Fey->AI_Controller->MoveToLocation(Destination);
	}
}
