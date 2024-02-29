#pragma once

#include "CoreMinimal.h"
#include "Enemy/States/EnemyStateBase.h"
#include "EnemyStateAlert.generated.h"

UCLASS()
class THELANDOFFEY_API UEnemyStateAlert : public UEnemyStateBase
{
	GENERATED_BODY()

protected:
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void TickState() override;
	virtual void OnExitState() override;

	void Alerted();
	void CheckSituation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Alert_Montage;

	FTimerHandle AlertTimerHandle;
	
};
