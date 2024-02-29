// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerStateBase.h"
#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Actor.h"
#include "PlayerStateAbilityA.generated.h"

/**
 * 
 */
UCLASS()
class THELANDOFFEY_API UPlayerStateAbilityA : public UPlayerStateBase
{
	GENERATED_BODY()





protected:

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> SlopeToSpawn;

	AActor* SpawnedSlopeActor = nullptr;

	FTimerHandle SlopeTimerHandle;

	virtual void TickState() override;
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void OnExitState() override;

	void UseAbilityA();
	void SpawnObject();
	void DestroyObject();

	void BackToIdle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)		//var to assign the montage
	UAnimMontage* Ability_A_Montage;

	FTimerHandle AbilityResetTimerHandle;

	//how long the character animation takes / when to exit ability state
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float AbilityDuration = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float DestroySlopeTime = 4.f;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	TSubclassOf<AActor> Slope;
	
};
