#include "Enemy/States/EnemyStateIdle.h"
#include "Enemy/EnemyAIController.h"

void UEnemyStateIdle::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);

	IdleTime = 0.f;
	bIsIdleAnimationPlaying = false;
}

void UEnemyStateIdle::TickState()
{
	Super::TickState();

	IdleTime += GetWorld()->GetDeltaSeconds();															//count (increment) idle time
		
	if (IdleAnimCooldownTime > 0.0f)																	//decrease the cooldown time if it's greater than zero
	{
		IdleAnimCooldownTime -= GetWorld()->GetDeltaSeconds();										
	}

	if (Fey->AI_Controller->bIsPlayerDetected)															//if player detected
	{
		if (!IsAlerted)																				//if not alerted so far, then go to alert
		{
			Fey->StateManager->SwitchStateByKey("Alert");
		}																										
		else																							//if already alerted, then combat
		{
			Fey->StateManager->SwitchStateByKey("Combat");
		}
		
	}
	else if (IdleTime >= MaxIdleTime && !bIsIdleAnimationPlaying)										//if idle time exceeded and no anim playing, patrol
	{
		Fey->StateManager->SwitchStateByKey("Patrol");
	}

	//---SFX & ANIM
	if (!bIsIdleAnimationPlaying && IdleTime < MaxIdleTime && IdleAnimCooldownTime <= 0.0f)				//if no anim playing and idle time not exceeded and idleCooldown 0
	{
		float randomNum = FMath::FRandRange(0.f, 1.f);													//% possibility to play an animation
		if (randomNum > 0.97f)
		{
			Fey->Idle_SFX();
			RandomIdle();
		}
	}
}

void UEnemyStateIdle::OnExitState()
{
	Super::OnExitState();

	GetWorld()->GetTimerManager().ClearTimer(IdleTimerHandle);											//clear anim timer
	GetWorld()->GetTimerManager().ClearTimer(CooldownTimerHandle);										//clear cooldown timer
}

void UEnemyStateIdle::RandomIdle()
{
	if (bIsIdleAnimationPlaying || IdleAnimCooldownTime > 0.0f)
	{
		return;
	}

	TArray<UAnimMontage*> AnimList;																		//create array of AnimMontages and add all anims
	AnimList.Add(Idle_Anim_1);
	AnimList.Add(Idle_Anim_2);
	AnimList.Add(Idle_Anim_3);

	int32 RandomIndex = FMath::RandRange(0, AnimList.Num() - 1);										//random number between 0 and the length of AnimList

	UAnimMontage* SelectedAnim = AnimList[RandomIndex];													//var to store the selected anim at the randomIndex

	if (!Fey->AI_Controller->bIsPlayerDetected)															//random idle animation
	{
		FeyAnimInstance->Montage_Play(SelectedAnim);
		bIsIdleAnimationPlaying = true;
		
		GetWorld()->GetTimerManager().ClearTimer(IdleTimerHandle);										//clear existing timers before setting new ones
		GetWorld()->GetTimerManager().ClearTimer(CooldownTimerHandle);
			
		GetWorld()->GetTimerManager().SetTimer(IdleTimerHandle, [this]() { bIsIdleAnimationPlaying = false; }, SelectedAnim->GetPlayLength(), false);							//when anim finished, set bool back to false
		GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, [this]() { IdleAnimCooldownTime = IdleAnimCooldown; }, SelectedAnim->GetPlayLength(), false);				//when anim finished, set cooldown (of 6 secs)
	}
}
