#pragma once

#include "CoreMinimal.h"
#include "Enemy/States/EnemyStateBase.h"
#include "EnemyStateCombat.generated.h"


UCLASS()
class THELANDOFFEY_API UEnemyStateCombat : public UEnemyStateBase
{
	GENERATED_BODY()
	
protected:
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void TickState() override;
	virtual void OnExitState() override;

	void ChooseAction();
};
