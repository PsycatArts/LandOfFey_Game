#pragma once

#include "CoreMinimal.h"
#include "Enemy/States/EnemyStateBase.h"
#include "EnemyStateIdle.generated.h"


UCLASS()
class THELANDOFFEY_API UEnemyStateIdle : public UEnemyStateBase
{
	GENERATED_BODY()

protected:
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void TickState() override;
	virtual void OnExitState() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Idle_Anim_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Idle_Anim_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Idle_Anim_3;


private:
	void RandomIdle();
														//time which enemy can spend in idle before switching
	FTimerHandle IdleTimerHandle;							
	float IdleTime;										//time remaining (timer )
	const float MaxIdleTime = 5.f;						//idle for maximum X seconds before switching to patrol

														//time after which idle animation can be played again
	FTimerHandle CooldownTimerHandle;
	float IdleAnimCooldownTime = 0.f;					//time remaining (timer )
	const float IdleAnimCooldown = 3.f;				//duration of cooldown


	bool bIsIdleAnimationPlaying;
	
};
