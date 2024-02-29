#pragma once

#include "CoreMinimal.h"
#include "Enemy/States/EnemyStateBase.h"
#include "EnemyStateStun.generated.h"


UCLASS()
class THELANDOFFEY_API UEnemyStateStun : public UEnemyStateBase
{
	GENERATED_BODY()
	
protected:
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void TickState() override;
	virtual void OnExitState() override;

	void Stun();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Stun_Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StunDuration = 2.f;

	FTimerHandle StunTimer;
};
