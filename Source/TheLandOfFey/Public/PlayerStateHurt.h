// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerStateBase.h"
//#include "Camera/CameraShake.h"
#include "PlayerStateHurt.generated.h"



/**
 * 
 */
UCLASS()
class THELANDOFFEY_API UPlayerStateHurt : public UPlayerStateBase
{
	GENERATED_BODY()
protected:

	//virtual void TakingDamage() override;
	virtual void TickState() override;
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void OnExitState() override;

	void ReturnToIdle();
	void Invincibility();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)		//var to assign the montage
	UAnimMontage* Hurt_Montage;
	//timer
	FTimerHandle HurtTimer;
	FTimerHandle InvincibilityTimer;

	//Time that player stays in hurt state (match the animation)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
	float Hurt_Time;

	//the seconds in which the player is invulnerable right after he was hurt
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//float i_Frames_Time;

	//UPROPERTY(EditDefaultsOnly, Category = "Screen Shake")
	//TSubclassOf<UCameraShake> HitShakeClass;
	
};
