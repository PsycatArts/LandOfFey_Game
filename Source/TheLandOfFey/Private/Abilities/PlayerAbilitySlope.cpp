// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/PlayerAbilitySlope.h"

void UPlayerAbilitySlope::OnStartAbility(AActor* AbilityOwner)
{
	Super::OnStartAbility(AbilityOwner);


	if (!Player)
	{
		Player = Cast<ATheLandOfFeyCharacter>(AbilityOwner);
	}
}

void UPlayerAbilitySlope::TickAbility()
{
	Super::TickAbility();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, TEXT("Player Ability Slope TICK"));
}

void UPlayerAbilitySlope::OnEndAbility()
{
	Super::OnEndAbility();
}

void UPlayerAbilitySlope::Use()
{
	Super::Use();

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Player Ability Slope"));
	SpawnSlope();
}

void UPlayerAbilitySlope::SpawnSlope()
{
	DestroySlope();
	if (!Player) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Player Ability Slope : No player found"));

	}
	//spawn slope
	FVector SpawnLocation = Player->GetActorLocation() + Player->GetActorForwardVector() * 100.0f;
	FRotator SpawnRotation = Player->GetActorRotation();
	if (SpawnedSlopeActor) 
	{
		SpawnedSlopeActor = GetWorld()->SpawnActor<AActor>(SlopeToSpawn, SpawnLocation, SpawnRotation);
	}
	

	//to destroy slope after x secs
	//FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	//TimerManager.SetTimer(SlopeTimerHandle, this, &UPlayerAbilitySlope::DestroySlope, DestroySlopeTime, false);
}

void UPlayerAbilitySlope::DestroySlope()
{
}
