#include "NotifyStateiFrames.h"

void UNotifyStateiFrames::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		Player = Cast<ATheLandOfFeyCharacter>(MeshComp->GetOwner());	
		if (Player)														
		{
			//activate iframes
			Player->Activate_I_Frames();
		}
	}
}

void UNotifyStateiFrames::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (Player)														
		{
			//deactivate iframes
			Player->Deactivate_I_Frames();
		}
	}
}
