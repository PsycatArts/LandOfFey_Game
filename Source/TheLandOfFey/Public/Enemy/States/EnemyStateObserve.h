#pragma once

#include "CoreMinimal.h"
#include "Enemy/States/EnemyStateBase.h"
#include "EnemyStateObserve.generated.h"


UCLASS()
class THELANDOFFEY_API UEnemyStateObserve : public UEnemyStateBase
{
	GENERATED_BODY()

protected:
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void TickState() override;
	virtual void OnExitState() override;

	void Observe();
	void CheckSituation();
	void CreateDistance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)									//distance that enemy will try to keep from player while observing  (will move away if necessary)
	float ObserveDistance = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Observe_Montage;

	FTimerHandle CheckingTimerHandle;



};
