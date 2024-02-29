// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerStateBase.h"
#include "PlayerStateStun.generated.h"

/**
 * 
 */
UCLASS()
class THELANDOFFEY_API UPlayerStateStun : public UPlayerStateBase
{
	GENERATED_BODY()

protected:
	virtual void TickState() override;
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void OnExitState() override;

	void ResettingStun();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)		//var to assign the montage
	UAnimMontage* Stun_Montage;

	FTimerHandle StunTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)		//var to assign the montage
	float Stun_Time;
};
