// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ElementBase.h"
#include "ElementDark.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class THELANDOFFEY_API UElementDark : public UElementBase
{
	GENERATED_BODY()

protected:


	virtual void OnEnterElement(AActor* ElementOwner) override;		//begin of state start
	virtual void TickElement() override;							//ticking state
	virtual void OnExitElement() override;							//end (destory/exit) if state

};
