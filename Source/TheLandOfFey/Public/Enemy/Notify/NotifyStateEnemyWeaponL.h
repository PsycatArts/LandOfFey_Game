// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NotifyStateEnemyWeaponL.generated.h"


class AFeyAI;


UCLASS()
class THELANDOFFEY_API UNotifyStateEnemyWeaponL : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UPROPERTY()
		AFeyAI* Fey;


	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;	//from engine source code of (animNotify file)

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	
};
