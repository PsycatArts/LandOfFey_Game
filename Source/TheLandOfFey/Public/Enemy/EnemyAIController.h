// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class THELANDOFFEY_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();




	//DETECTION BOOL (further used in enemy base class)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	bool bIsPlayerDetected = false;

	//DISTANCE TO PLAYER (further used in enemy base class)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	float C_DistanceToPlayer = 0.0f;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")			//sight radius of AI
	float AISightRadius = 1000.0f;

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;

	//pawn detection component setup
	UFUNCTION(BlueprintCallable)
	void OnPawnDetected(const TArray<AActor*>& DetectedPawns);


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")			//how long object is kept in memory after AI detected it 
	float AISightAge = 20.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")			//the padding range in which playerSight will maintain if running away
	float AILoseSightRadius = AISightRadius + 800.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	float AIFieldOfView = 360.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	class UAISenseConfig_Sight* SightConfig;


	
};
