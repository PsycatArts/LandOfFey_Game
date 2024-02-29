// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "TheLandOfFey/TheLandOfFeyCharacter.h"
#include "NotifyStateiFrames.generated.h"

class ATheLandOfFeyCharacter;

UCLASS()
class THELANDOFFEY_API UNotifyStateiFrames : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UPROPERTY()
	ATheLandOfFeyCharacter* Player;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;	//from engine source code of (animNotify file)

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};
