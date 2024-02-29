// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/FeyStateBase.h"
#include "FeyStateObserve.generated.h"

/**
 * 
 */
UCLASS()
class THELANDOFFEY_API UFeyStateObserve : public UFeyStateBase
{
	GENERATED_BODY()

protected:
	virtual void TickState() override;
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void OnExitState() override;


	void Observing();

	void MoveAwayFromPlayer();

	//Montage to play when Player detected (before going over to combat)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Observing_Montage;

	FTimerHandle ObservingTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ObserveDistance = 500.f;

	void CheckSituation();
	FTimerHandle CheckingTimerHandle;
	
};
