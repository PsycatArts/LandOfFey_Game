// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityBase.h"
#include "TheLandOfFey/TheLandOfFeyCharacter.h"
#include "PlayerAbilitySlope.generated.h"

/**
 * 
 */
UCLASS()
class THELANDOFFEY_API UPlayerAbilitySlope : public UAbilityBase
{
	GENERATED_BODY()


public:
	UPROPERTY(BlueprintReadOnly)
		ATheLandOfFeyCharacter* Player;


	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> SlopeToSpawn;

	AActor* SpawnedSlopeActor = nullptr;

	FTimerHandle SlopeTimerHandle;

	virtual void OnStartAbility(AActor* AbilityOwner) override;
	virtual void TickAbility() override;
	virtual void OnEndAbility() override;
	virtual void Use() override;

	//void Use();
	void SpawnSlope();
	void DestroySlope();

	FTimerHandle AbilityResetTimerHandle;

	//how long the character animation takes / when to exit ability state
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float AbilityDuration = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float DestroySlopeTime = 4.f;
	
};
