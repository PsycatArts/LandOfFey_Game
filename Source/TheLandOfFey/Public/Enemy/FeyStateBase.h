#pragma once

#include "CoreMinimal.h"
#include "StateBase.h"
#include "FeyAI.h"
#include "FeyStateBase.generated.h"

//Class serves as BASE state for all other state machines
UCLASS()
class THELANDOFFEY_API UFeyStateBase : public UStateBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	AFeyAI* Fey;

	virtual void OnEnterState(AActor* OwnerRef) override;
	virtual void OnExitState() override;

	//IF PLAYER WITHIN THIS RANGE, AI WILL ATTACK (further used in meleeattack & chase state)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float RangeToAttack = 200.0f;

	bool IsAllerted;
	
};
