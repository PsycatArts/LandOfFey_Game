// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/FeyStateBase.h"
#include "FeyStateDeath.generated.h"

/**
 * 
 */
UCLASS()
class THELANDOFFEY_API UFeyStateDeath : public UFeyStateBase
{
	GENERATED_BODY()

protected:
	virtual void TickState() override;
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void OnExitState() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)		//var to assign the montage
	UAnimMontage* Death_Montage;
	
};
