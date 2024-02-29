// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/FeyStateBase.h"
#include "FeyStateIdle.generated.h"

/**
 * 
 */
UCLASS()
class THELANDOFFEY_API UFeyStateIdle : public UFeyStateBase
{
	GENERATED_BODY()
protected:
	virtual void TickState() override;
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void OnExitState() override;


};
