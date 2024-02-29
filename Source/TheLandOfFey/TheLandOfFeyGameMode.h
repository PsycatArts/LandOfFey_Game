// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Enemy/EnemyManager.h"
#include "Sound/SoundManager.h"
#include "TheLandOfFeyGameMode.generated.h"

UCLASS(minimalapi)
class ATheLandOfFeyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATheLandOfFeyGameMode();

	UPROPERTY(BlueprintReadWrite)
	AEnemyManager* EnemyManagerInstance;

	ASoundManager* SoundManagerInstance;

	virtual void BeginPlay() override;


	ASoundManager* GetSoundManager();
};



