#pragma once

#include "CoreMinimal.h"
#include "Enemy/States/EnemyStateBase.h"
#include "EnemyStateMelee.generated.h"

UCLASS()
class THELANDOFFEY_API UEnemyStateMelee : public UEnemyStateBase
{
	GENERATED_BODY()

protected:
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void TickState() override;
	virtual void OnExitState() override;

	void MeleeAttack();
	FName GetAttackSectionName(int32 SectionCount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Melee_Montage;

	FTimerHandle TimerToResetAttackState;					

	float AttackTimer;      // Current remaining cooldown time
	float AttackCooldown;  // Total cooldown duration

};
