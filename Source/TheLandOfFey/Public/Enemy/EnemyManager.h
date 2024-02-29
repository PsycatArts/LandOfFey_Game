// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundManager.h"
#include "EnemyManager.generated.h"

class AEnemyAI;

UCLASS()
class THELANDOFFEY_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddAllertedEnemy(AEnemyAI* Enemy);

	UFUNCTION(BlueprintCallable)
	void RemoveAllertedEnemy(AEnemyAI* Enemy);

	void CheckAndChangeState();
	void CheckAndChangeAttackState();

	void AlertCloseEnemies(AEnemyAI* Enemy);

	void SetSoundManager(ASoundManager* SoundManagerRef);
	void GetSoundManager();

	UPROPERTY(BlueprintReadWrite)
	TArray<AEnemyAI*> AllertedEnemies;


	UPROPERTY(BlueprintReadWrite)
	TArray<AEnemyAI*> AttackingEnemies;

	UPROPERTY(BlueprintReadWrite)
	ASoundManager* SoundManager;

};
