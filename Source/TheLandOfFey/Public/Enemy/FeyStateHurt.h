// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraFunctionLibrary.h"
#include "Enemy/FeyStateBase.h"
#include "FeyStateHurt.generated.h"

/**
 * 
 */
UCLASS()
class THELANDOFFEY_API UFeyStateHurt : public UFeyStateBase
{
	GENERATED_BODY()


protected:
	virtual void TickState() override;
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void OnExitState() override;

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

	void ReturnToIdle();

	//time that player is in hurt state.. fit to animation
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//float Hurt_Time;

	UPROPERTY(EditAnywhere, Category = "Effects")
	class UNiagaraSystem* NiagaraParticle_Neutral;
	
	UPROPERTY(EditAnywhere, Category = "Effects")
	class UNiagaraSystem* NiagaraParticle_Light;

	UPROPERTY(EditAnywhere, Category = "Effects")
	class UNiagaraSystem* NiagaraParticle_Dark;

};
