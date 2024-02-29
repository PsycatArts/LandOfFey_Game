#include "Enemy/States/EnemyStateKnockback.h"
#include "GameFramework/Character.h"

void UEnemyStateKnockback::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

	if (Fey->GetIsDead()) return;

	FVector PlayerLocation= Player->GetActorLocation();

	Fey->RotateTowardsPlayer();
	Knockback(PlayerLocation, KnockbackStrength);
	PlayKnockbackAnim();
}

void UEnemyStateKnockback::TickState()
{
	Super::TickState();
}

void UEnemyStateKnockback::OnExitState()
{
	Super::OnExitState();
}

void UEnemyStateKnockback::Knockback(FVector SourceLocation, float Knockback)																//knockback away from player
{
	FVector KnockbackDirection = Fey->GetActorLocation() - SourceLocation;
	KnockbackDirection.Normalize();
	KnockbackDirection.Z = 0.6f;
	Fey->LaunchCharacter(KnockbackDirection * Knockback, true, true);
}

void UEnemyStateKnockback::PlayKnockbackAnim()
{
	Fey->Knockback_SFX();

	UWorld* World = GetWorld();																												//---VFX--
	FVector ParticleLocation = Fey->GetActorLocation();
	ParticleLocation.Z += 60.0f;																											//vertical offset (Z-Axis)
	FRotator ParticleRotation(0.f, 0.f, 0.f);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Knockback_Niagara_Particle, ParticleLocation, ParticleRotation);

	float MontageDuration;																													//---ANIM
	if(FeyAnimInstance && Knockback_Montage)
	{
		MontageDuration = FeyAnimInstance->Montage_Play(Knockback_Montage);
		GetWorld()->GetTimerManager().SetTimer(KnockbackTimerHandle , this, &UEnemyStateKnockback::BackToCombat, MontageDuration);
	}
}

