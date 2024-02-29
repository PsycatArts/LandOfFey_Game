#pragma once

#include "CoreMinimal.h"
#include "Enemy/States/EnemyStateBase.h"
#include "EnemyStateDeath.generated.h"


UCLASS()
class THELANDOFFEY_API UEnemyStateDeath : public UEnemyStateBase
{
	GENERATED_BODY()

protected:
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void TickState() override;
	virtual void OnExitState() override;

	void Death();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
	UAnimMontage* Death_Montage;
};
