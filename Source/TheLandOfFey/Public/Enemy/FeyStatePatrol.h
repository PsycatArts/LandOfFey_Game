// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/FeyStateBase.h"
#include "FeyStatePatrol.generated.h"

/**
 * 
 */
UCLASS()
class THELANDOFFEY_API UFeyStatePatrol : public UFeyStateBase
{
	GENERATED_BODY()

protected:
	virtual void TickState() override;
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void OnExitState() override;

	FTimerHandle PatrolTimer;

	void Patrolling();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Patrol_Range = 1000.f;


	//void Allerted();
	void StartCombat();

	////Montage to play when Player detected (before going over to combat)
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//UAnimMontage* Allerted_Montage;

	//FTimerHandle AllertedTimerHandle;

	

	
};
