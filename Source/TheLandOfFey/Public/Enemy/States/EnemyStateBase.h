// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "StateBase.h"
#include "Enemy/FeyAI.h"
#include "TheLandOfFey/TheLandOfFeyCharacter.h"
#include "EnemyStateBase.generated.h"


UCLASS()
class THELANDOFFEY_API UEnemyStateBase : public UStateBase
{
	GENERATED_BODY()

public:

	virtual void OnEnterState(AActor* OwnerRef) override;
	virtual void OnExitState() override;

	UPROPERTY(BlueprintReadOnly)
	AFeyAI* Fey;

	UPROPERTY(BlueprintReadOnly)
	ATheLandOfFeyCharacter* Player;

	UAnimInstance* FeyAnimInstance;


	bool IsAlerted;

	void DeactivateMovement();
	void ReactivateMovement();

	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)					//used for melee & Chase
	float AttackRange = 170.f;

	void BackToCombat();
	
};
