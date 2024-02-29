// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Notify/NotifyStateEnemyWeaponL.h"
#include "Enemy/FeyAI.h"

void UNotifyStateEnemyWeaponL::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		Fey = Cast<AFeyAI>(MeshComp->GetOwner());		//cast to thirdPersonCharacter to get the mesh component, else crash
		if (Fey)														//validation check (if it exists..)
		{
			Fey->ActivateWeaponL();

		}
	}
}

void UNotifyStateEnemyWeaponL::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (Fey)														//validation check (if it exists..)
		{
			Fey->DeactivateWeaponL();
		}
	}
}
