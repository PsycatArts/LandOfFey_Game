#include "Enemy/States/EnemyStateHurt.h"
#include "Math/UnrealMathUtility.h"

void UEnemyStateHurt::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

	Hurt();
}

void UEnemyStateHurt::TickState()
{
	Super::TickState();
}

void UEnemyStateHurt::OnExitState()
{
	Super::OnExitState();
	GetWorld()->GetTimerManager().ClearTimer(HurtTimerHandle);											//clear timer
}

void UEnemyStateHurt::Hurt()
{
	Fey->IsHurting = true;

	//small knockback
	FVector KnockbackDirection = Fey->GetActorLocation() - Player->GetActorLocation();		//means direction is away from player
	KnockbackDirection.Normalize();															//normalize/ensure direction vector has a length of 1
	KnockbackDirection.Z = 0.2f;															//upward force
	Fey->LaunchCharacter(KnockbackDirection * Knockback_Strength, true, true);

	//---VFX--
	Fey->Hurt_Shader();

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
	else if (!Player->ElementSystem->CurrentElement && NiagaraParticle_Neutral)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraParticle_Neutral, ParticleLocation, ParticleRotation);

	}

	//---SFX---
	float randomHurtNum = FMath::FRandRange(0.f, 1.f);													//% possibility to play hurt
	if (randomHurtNum > 0.5f)
	{
		Fey->Hurt_SFX();
	}

	//--- ANIMATION ---
	float MontageTime = 0.0f;

	UAnimInstance* AnimInstance = Fey->GetMesh()->GetAnimInstance();
	
	float randomNum = FMath::FRandRange(0.f, 1.f);									//for possibility to break free after 3rd hit

	switch (Hurt_Num)
	{
	case 0:
		MontageTime = AnimInstance->Montage_Play(Hurt_Montage_1);
		Hurt_Num++;
		break;
	case 1:
		MontageTime = AnimInstance->Montage_Play(Hurt_Montage_2);
		Hurt_Num++;
		break;
	case 2:
		MontageTime = AnimInstance->Montage_Play(Hurt_Montage_3);
		Hurt_Num++;
		Hurt_Num = 0;
		if (randomNum > 0.40f)														//possibility of 60%  to go to attack immediatly and break free from constant hurt
		{
			Fey->StateManager->SwitchStateByKey("Melee");
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("BREAKING FREE"));
		}
		break;

	default:
		Hurt_Num = 0;
	}

	GetWorld()->GetTimerManager().SetTimer(HurtTimerHandle, this, &UEnemyStateHurt::ToIdle, MontageTime);		//back to combat after hurt anim
}

void UEnemyStateHurt::ToIdle()
{
	//if not dead
	if (Fey->Health > 0.f)
	{
		Fey->StateManager->SwitchStateByKey("Combat");
	}
}
