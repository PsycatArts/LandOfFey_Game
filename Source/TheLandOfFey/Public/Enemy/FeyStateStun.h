// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/FeyStateBase.h"
#include "FeyStateStun.generated.h"

/**
 * 
 */
UCLASS()
class THELANDOFFEY_API UFeyStateStun : public UFeyStateBase
{
	GENERATED_BODY()

protected:


	virtual void TickState() override;
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void OnExitState() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* Stun_Montage;

	FTimerHandle StunTimer;

	void BackToCombat();

	//set in editor, how long the stun takes to be finished 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float StunDuration = 2.f;

	
};
