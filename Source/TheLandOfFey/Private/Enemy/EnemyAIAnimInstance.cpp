// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyAIAnimInstance.h"
#include "Enemy/EnemyAI.h"
#include "Kismet/KismetMathLibrary.h"

/// <summary>
/// Class Enemy animation instance:
/// Inherited by Enemy AnimationBlueprint to use custom Update
/// </summary>
/// 
void UEnemyAIAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	// CHECK IF ENEMY OBJECT EXISTS
	if (Enemy == nullptr)
	{
		//
		Enemy = Cast<AEnemyAI>(TryGetPawnOwner());
	}

	if (Enemy /*&& !Death*/)
	{

	//lateral speed of enemy from velocity
	FVector Velocity{ Enemy->GetVelocity() };		//getting velocity of char (like in blueprint)
	Velocity.Z = 0;									//zero out the Z velocity
	Speed = Velocity.Size();						//assign speed to char's velocity
	Death = Enemy->GetIsDead();

	//get offset yaw used in blendSpace
	const FRotator AimRotation = Enemy->GetBaseAimRotation();

	//getting the rotation direction of aim
	const FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(Enemy->GetVelocity());

	MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;
	}

}
