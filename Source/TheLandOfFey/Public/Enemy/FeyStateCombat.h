// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/FeyStateBase.h"
#include "FeyStateCombat.generated.h"

/**
 * 
 */
UCLASS()
class THELANDOFFEY_API UFeyStateCombat : public UFeyStateBase
{
	GENERATED_BODY()

protected:
	virtual void TickState() override;
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void OnExitState() override;

	//timer to handle the time to attack again
	FTimerHandle AttackTimer;

	void SwitchToAttack();

	void DecideNextAction();

	void CircleAroundPlayer(float Distance, float CircleSpeed);


	FTimerHandle CircleTimerHandle;
	FVector TargetLocation;
	void UpdateTargetLocation(float Distance);
};
