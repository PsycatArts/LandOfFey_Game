#include "Enemy/States/EnemyStatePatrol.h"
#include "Enemy/EnemyAIController.h"
#include "NavigationSystem.h"
#include "GameFramework/CharacterMovementComponent.h"

void UEnemyStatePatrol::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

    Fey->GetCharacterMovement()->MaxWalkSpeed = 300.f;
	RandomPatrol();

    GetWorld()->GetTimerManager().SetTimer(PatrolTimerHandle, this, &UEnemyStatePatrol::PatrolTimeout, PatrolTimeoutDuration, false);       //start patrol timeout timer
}

void UEnemyStatePatrol::TickState()
{
	Super::TickState();

    if (FVector::DistSquared(Fey->GetActorLocation(), Destination) < 100.f * 100.f)                                                         //if distance to destination small enough, consider the patrol finished.. error margin of 200x200
    {
        Fey->StateManager->SwitchStateByKey("Idle");
    }
    else if (Fey->AI_Controller->bIsPlayerDetected)
    {
        Fey->StateManager->SwitchStateByKey("Alert");
    }
}

void UEnemyStatePatrol::OnExitState()
{
	Super::OnExitState();

    GetWorld()->GetTimerManager().ClearTimer(PatrolTimerHandle);
}

void UEnemyStatePatrol::RandomPatrol()
{	
    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(Fey->GetWorld());
    FNavLocation RandomPoint;
    if (NavSys->GetRandomPointInNavigableRadius(Fey->GetActorLocation(), Patrol_Range, RandomPoint))
    {
        Destination = RandomPoint.Location;
        
        if (Fey->AI_Controller)                                         
        {
            Fey->AI_Controller->MoveToLocation(Destination);
        }
    }
}

void UEnemyStatePatrol::PatrolTimeout()
{
    Fey->StateManager->SwitchStateByKey("Idle");
}
