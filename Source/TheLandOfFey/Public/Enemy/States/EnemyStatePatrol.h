#pragma once

#include "CoreMinimal.h"
#include "Enemy/States/EnemyStateBase.h"
#include "EnemyStatePatrol.generated.h"


UCLASS()
class THELANDOFFEY_API UEnemyStatePatrol : public UEnemyStateBase
{
	GENERATED_BODY()

protected:
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void TickState() override;
	virtual void OnExitState() override;

	void RandomPatrol();											//patrol to random point	
	void PatrolTimeout();											//if patrol doesnt reach point within time.. 


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Patrol_Range = 1000.f;

	float PatrolTimeoutDuration = 7.f;

	FTimerHandle PatrolTimerHandle;

	FVector Destination;




};
