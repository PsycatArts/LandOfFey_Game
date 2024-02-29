// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/FeyStateHurt.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TheLandOfFey/TheLandOfFeyCharacter.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"	
#include "Math/UnrealMathUtility.h"
#include "Animation/AnimInstance.h"
#include "NiagaraComponent.h"

void UFeyStateHurt::TickState()
{
	Super::TickState();
	if (Fey->Health <= 0) 
	{
		Fey->StateManager->SwitchStateByKey("Death");
	}
	//Fey->GetCharacterMovement()->StopMovementImmediately();
	//Fey->GetCharacterMovement()->DisableMovement();
}

void UFeyStateHurt::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

	Fey->IsHurting = true;

	ATheLandOfFeyCharacter* Player = Cast<ATheLandOfFeyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player == nullptr)
		return;

	//small knockback
	FVector KnockbackDirection = Fey->GetActorLocation() - Player->GetActorLocation();		//means direction is away from player
	KnockbackDirection.Normalize();															//normalize/ensure direction vector has a length of 1
	KnockbackDirection.Z = 0.2f;															//upward force
	Fey->LaunchCharacter(KnockbackDirection * Knockback_Strength, true, true);

	//---VFX--
	UWorld* World = GetWorld();
	FVector ParticleLocation = Fey->GetActorLocation();
	ParticleLocation.Z += 60.0f;						//vertical offset (Z-Axis)
	FRotator ParticleRotation(0.f, 0.f, 0.f);

	if (Player->ElementSystem->CurrentElement && World)
	{
		if (Player->ElementSystem->CurrentElement->ElementDisplayName == "Light" && NiagaraParticle_Light)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraParticle_Light, ParticleLocation, ParticleRotation);
		}
		else if (Player->ElementSystem->CurrentElement->ElementDisplayName == "Dark" && NiagaraParticle_Dark)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraParticle_Dark, ParticleLocation, ParticleRotation);
		}
	}
	else if(!Player->ElementSystem->CurrentElement && NiagaraParticle_Neutral)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraParticle_Neutral, ParticleLocation, ParticleRotation);

	}

	//--- ANIMATION ---
	//Fey->GetCharacterMovement()->StopMovementImmediately();
	//Fey->GetCharacterMovement()->DisableMovement();

	float MontageTime = 0.0f;

	UAnimInstance* AnimInstance = Fey->GetMesh()->GetAnimInstance();

	//for possibility to break free after 3rd hit
	float randomNum = FMath::FRandRange(0.f, 1.f);

	switch (Hurt_Num)
	{
	case 0:
		MontageTime= AnimInstance->Montage_Play(Hurt_Montage_1);
		Hurt_Num++;
		break;
	case 1:
		MontageTime= AnimInstance->Montage_Play(Hurt_Montage_2);
		Hurt_Num++;
		break;
	case 2:
		MontageTime= AnimInstance->Montage_Play(Hurt_Montage_3);
		Hurt_Num++;
		Hurt_Num = 0;
		//possibility of 50%  to go to attack immediatly and break free from constant hurt
		if (randomNum > 0.50f)
		{
			Fey->StateManager->SwitchStateByKey("MeeleAttack");
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("BREAKING FREE"));
		}
		break;

	default:
		Hurt_Num = 0;
	}

	GetWorld()->GetTimerManager().SetTimer(HurtTimerHandle, this, &UFeyStateHurt::ReturnToIdle, MontageTime);
}

void UFeyStateHurt::OnExitState()
{
	Super::OnExitState();

	Fey->IsHurting = false;
	Fey->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

void UFeyStateHurt::ReturnToIdle()
{
	//if not dead
	if (Fey->Health > 0.f )
	{
		Fey->StateManager->SwitchStateByKey("Combat");
	}
	else 
	{
		Fey->StateManager->SwitchStateByKey("Death");
	}
}
