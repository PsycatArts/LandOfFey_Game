// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/FeyStateDeath.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "Components/CapsuleComponent.h"

void UFeyStateDeath::TickState()
{
	Super::TickState();
}

void UFeyStateDeath::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

	//if (!Fey->IsDead) 
	//{
		Fey->IsDead = true;

		Fey->Health = 0.f;
		Fey->EnemyManager->RemoveAllertedEnemy(Fey);

		Fey->GetCharacterMovement()->DisableMovement();
		UCapsuleComponent* CapsuleComponent = Fey->GetCapsuleComponent();
		if (CapsuleComponent)
		{
			CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}


		UAnimInstance* AnimInstance = Fey->GetMesh()->GetAnimInstance();
		if (Death_Montage)
		{
			AnimInstance->Montage_Play(Death_Montage);

		}
	//}

}

void UFeyStateDeath::OnExitState()
{
	Super::OnExitState();
}
