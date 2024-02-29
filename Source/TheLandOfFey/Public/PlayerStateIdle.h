// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerStateBase.h"
#include "PlayerStateIdle.generated.h"

/**
 * 
 */
UCLASS()
class THELANDOFFEY_API UPlayerStateIdle : public UPlayerStateBase
{
	GENERATED_BODY()
	
protected:
	virtual void TickState() override;
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void OnExitState() override;
};
