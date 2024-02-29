// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheLandOfFey/TheLandOfFeyCharacter.h"
#include "PlayerStateAttack.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NotifyStatePlayerWeapon.generated.h"

//declarations
class ATheLandOfFeyCharacter;
class UPlayerStateAttack;

UCLASS()
class THELANDOFFEY_API UNotifyStatePlayerWeapon : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UPROPERTY()
	ATheLandOfFeyCharacter* Player;
	UPROPERTY()
	UPlayerStateAttack* Attack;



	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;	//from engine source code of (animNotify file)

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};
