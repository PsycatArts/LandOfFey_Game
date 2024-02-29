// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/FeyStateBase.h"
#include "FeyStateMeeleAttack.generated.h"

/**
 * 
 */
UCLASS()
class THELANDOFFEY_API UFeyStateMeeleAttack : public UFeyStateBase
{
	GENERATED_BODY()

protected:
	virtual void TickState() override;
	virtual void OnEnterState(AActor* StateOwner) override;

	virtual void OnExitState() override;

	//Montage for melee attacks (set in BP)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* MeeleAttack_Montage;



	void ReturnToCombat();

	void MeeleAttack();

	FTimerHandle TimerToResetAttackState;
	FName GetAttackSectionName(int32 SectionCount);
	
};
