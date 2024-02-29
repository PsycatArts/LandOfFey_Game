// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/FeyStateBase.h"
#include "FeyStateAllert.generated.h"

/**
 * 
 */
UCLASS()
class THELANDOFFEY_API UFeyStateAllert : public UFeyStateBase
{
	GENERATED_BODY()

protected:
	virtual void TickState() override;
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void OnExitState() override;

	void Allerted();

	void StartCombat();
	void CheckSituation();


	//Montage to play when Player detected (before going over to combat)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Allerted_Montage;

	FTimerHandle AllertedTimerHandle;
	
};
