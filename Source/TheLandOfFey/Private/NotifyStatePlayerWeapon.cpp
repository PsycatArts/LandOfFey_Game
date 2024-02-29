// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyStatePlayerWeapon.h"


void UNotifyStatePlayerWeapon::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	//Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("My Notify Begin"));

	if (MeshComp && MeshComp->GetOwner())
	{
		Player = Cast<ATheLandOfFeyCharacter>(MeshComp->GetOwner());		//cast to thirdPersonCharacter to get the mesh component, else crash
		//Attack = Cast<UPlayerStateAttack>(MeshComp->GetOwner());
		if (Player /*&& Attack*/)														//validation check (if it exists..)
		{
			Player->ActivateWeapon();
		}
	}
}

void UNotifyStatePlayerWeapon::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	//Super::NotifyEnd(MeshComp, Animation, EventReference);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("My Notify End"));

	if (MeshComp && MeshComp->GetOwner())
	{
		//ThirdPersonChar = Cast<ATP_ThirdPersonCharacter>(MeshComp->GetOwner());		//cast to thirdPersonCharacter to get the mesh component, else crash
		if (Player/* && Attack*/)														//validation check (if it exists..)
		{
			Player->DeactivateWeapon();
		}
	}
}