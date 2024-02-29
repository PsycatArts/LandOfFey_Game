#pragma once

#include "CoreMinimal.h"
#include "PlayerStateBase.h"
#include "NiagaraFunctionLibrary.h"
#include "PlayerStateSwitchElement.generated.h"


UCLASS()
class THELANDOFFEY_API UPlayerStateSwitchElement : public UPlayerStateBase
{
	GENERATED_BODY()


protected:

	virtual void TickState() override;
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void OnExitState() override;

	void SwitchElement();

	void BackToIdle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)		//var to assign the montage
	UAnimMontage* SwitchElement_Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraSystem* NiagaraParticle_Neutral;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraSystem* NiagaraParticle_Light;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraSystem* NiagaraParticle_Dark;


	FTimerHandle SwitchResetTimerHandle;

	//set in editor, how long the ability takes to be finished 
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//float SwitchElementDuration = 0.5f;
	//void Parry();
};
