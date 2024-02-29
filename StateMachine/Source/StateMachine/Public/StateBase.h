#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StateBase.generated.h"


UCLASS(Blueprintable)
class STATEMACHINE_API UStateBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bCanTickState = false;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bCanRepeat = false;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FName StateDisplayName;


	virtual void OnEnterState(AActor* StateOwner);		//begin of state start
	virtual void TickState();							//ticking state
	virtual void OnExitState();							//end (destory/exit) if state							//reason to exit state
};
