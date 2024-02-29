// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateBase.h"
#include "TheLandOfFey/TheLandOfFeyCharacter.h"
#include "PlayerStateBase.generated.h"


/**
 * 
 */
UCLASS()
class THELANDOFFEY_API UPlayerStateBase : public UStateBase
{
	GENERATED_BODY()
	
public: 
	
	UPROPERTY(BlueprintReadOnly)
	ATheLandOfFeyCharacter* Player;

	virtual void OnEnterState(AActor* OwnerRef) override;
	virtual void OnExitState() override;

	virtual void Attacking();

	/*bool IsHurting;*/

	void DisablePlayerMovement();
	void EnablePlayerMovement();

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	//bool AttackTest;
};
