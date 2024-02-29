#pragma once

#include "CoreMinimal.h"
#include "Enemy/States/EnemyStateBase.h"
#include "NiagaraFunctionLibrary.h"
#include "EnemyStateKnockback.generated.h"

UCLASS()
class THELANDOFFEY_API UEnemyStateKnockback : public UEnemyStateBase
{
	GENERATED_BODY()

protected: 
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void TickState() override;
	virtual void OnExitState() override;

	void Knockback(FVector SourceLocation, float Knockback);
	void PlayKnockbackAnim();

	UPROPERTY(EditAnywhere, Category = "Effects")
	class UNiagaraSystem* Knockback_Niagara_Particle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Knockback_Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float KnockbackStrength = 600.f;

	FTimerHandle KnockbackTimerHandle;
	
};
