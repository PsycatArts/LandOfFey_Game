// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerStateBase.h"
#include "PlayerStateDodge.generated.h"

/**
 * 
 */
UCLASS()
class THELANDOFFEY_API UPlayerStateDodge : public UPlayerStateBase
{
	GENERATED_BODY()

	//virtual void TakingDamage() override;
	virtual void TickState() override;
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void OnExitState() override;

	void ReturnToIdle();

	void Dodge();

	FTimerHandle DodgeTimerHandle;


	// Animation
	UPROPERTY(EditAnywhere)
		UAnimMontage* DodgeForwardAnim;

	UPROPERTY(EditAnywhere)
		UAnimMontage* DodgeRightAnim;

	UPROPERTY(EditAnywhere)
		UAnimMontage* DodgeLeftAnim;

	UPROPERTY(EditAnywhere)
		UAnimMontage* DodgeBackAnim;
	
};
