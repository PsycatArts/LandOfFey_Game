// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAIAnimInstance.generated.h"

/// <summary>
/// Class Enemy animation instance:
/// Inherited by Enemy AnimationBlueprint to use custom Update
/// </summary>
/// 
class AEnemyAI;
/**
 * 
 */
UCLASS()
class THELANDOFFEY_API UEnemyAIAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	//ACTS AS TICK FUNCTION TO UPDATE ANIMATION PROPERTIES 
	UFUNCTION(BlueprintCallable)
		void UpdateAnimationProperties(float DeltaTime);

private:

	//Get enemy reference
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AEnemyAI* Enemy;

	//speed 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float Speed;

	//death of enemy
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	bool Death;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	//	bool Stunned;

	//offset used for strafing (not sure if will be used)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MovementOffsetYaw;
	
};
