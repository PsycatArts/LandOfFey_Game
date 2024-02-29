// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheLandOfFeyGameMode.h"
#include "TheLandOfFeyCharacter.h"
#include "EngineUtils.h"
#include "UObject/ConstructorHelpers.h"

ATheLandOfFeyGameMode::ATheLandOfFeyGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ATheLandOfFeyGameMode::BeginPlay()
{
	Super::BeginPlay();

	EnemyManagerInstance = GetWorld()->SpawnActor<AEnemyManager>();
	// Find the existing ASoundManager actor
	// Find the ASoundManager in the world and assign it to our variable
	for (TActorIterator<ASoundManager> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		SoundManagerInstance = *ActorItr;
		break;
	}

	if (SoundManagerInstance != nullptr)
	{
		EnemyManagerInstance->SetSoundManager(SoundManagerInstance);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No SoundManager found in the level."));
	}
}

ASoundManager* ATheLandOfFeyGameMode::GetSoundManager()
{
	return SoundManagerInstance;
}
