// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyAIController.h"
#include "Enemy/EnemyAI.h"
#include "TheLandOfFey/TheLandOfFeyCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "Enemy/EnemyAI.h"

AEnemyAIController::AEnemyAIController()
{
	//activate TICK function
	PrimaryActorTick.bCanEverTick = true;

	//PLAYER DETECTION COMPONENT

	//attach sight components to object
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	//setting the SightConfig variables 
	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);

	//setting detection of types
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	//will run the OnPawnDetected function if perception was updated
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnPawnDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);



	bIsPlayerDetected = false;
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	//if (GetPerceptionComponent() != nullptr) {
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Enemy AI: All systems set"));
	//}
	//else {
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Enemy AI: Error in system setting"));
	//}
}
void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AEnemyAI* Enemy = Cast<AEnemyAI>(InPawn);
}

void AEnemyAIController::Tick(float DeltaSeconds)
{

	Super::Tick(DeltaSeconds);

	

	//GET DISTANCE TO PLAYER
	ATheLandOfFeyCharacter* Player = Cast<ATheLandOfFeyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Player) return;
	FVector AILocation = GetPawn()->GetActorLocation();
	FVector PlayerLocation = Player->GetActorLocation();
	float DistanceToPlayer = FVector::Distance(AILocation, PlayerLocation);

	C_DistanceToPlayer = DistanceToPlayer;


	//IF PLAYER OUT OF SIGHT
	if (C_DistanceToPlayer > AISightRadius)
	{
		//DETECTION OFF
		bIsPlayerDetected = false;

	

		
	}
}

void AEnemyAIController::OnPawnDetected(const TArray<AActor*>& DetectedPawns)
{
	bIsPlayerDetected = true;
	//for each player detected..
	for (size_t i = 0; i < DetectedPawns.Num(); i++)
	{
		C_DistanceToPlayer = GetPawn()->GetDistanceTo(DetectedPawns[i]);
	}


	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("AI CONTROLLER: Player Detected"));

}
