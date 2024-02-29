#pragma once

#include "CoreMinimal.h"
#include "Enemy/States/EnemyStateBase.h"
#include "NiagaraFunctionLibrary.h"
#include "EnemyStateHurt.generated.h"

UCLASS()
class THELANDOFFEY_API UEnemyStateHurt : public UEnemyStateBase
{
	GENERATED_BODY()

protected:
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void TickState() override;
	virtual void OnExitState() override;

	void Hurt();
	void ToIdle();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Hurt_Montage_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Hurt_Montage_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Hurt_Montage_3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Knockback_Strength = 200.f;

	int Hurt_Num;
	FTimerHandle HurtTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Effects")
	class UNiagaraSystem* NiagaraParticle_Neutral;

	UPROPERTY(EditAnywhere, Category = "Effects")
	class UNiagaraSystem* NiagaraParticle_Light;

	UPROPERTY(EditAnywhere, Category = "Effects")
	class UNiagaraSystem* NiagaraParticle_Dark;
	
};
