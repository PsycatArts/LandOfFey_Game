#include "Enemy/EnemyManager.h"
#include "Enemy/EnemyAI.h"
#include "Enemy/EnemyAIController.h"
#include "TheLandOfFey/TheLandOfFeyCharacter.h"
#include "TheLandOfFey/TheLandOfFeyGameMode.h"
#include "Kismet/GameplayStatics.h"	
#include "Kismet/KismetSystemLibrary.h"

AEnemyManager::AEnemyManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//int32 CombatingEnemiesCount = AttackingEnemies.Num();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Number of Combating Enemies: %d"), CombatingEnemiesCount));
}

void AEnemyManager::GetSoundManager()
{
	// Cast the game mode to ATheLandOfFeyGameMode so we can access its methods
	ATheLandOfFeyGameMode* gameMode = Cast<ATheLandOfFeyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	// Get the SoundManager from the game mode
	if (gameMode)
	{
		SoundManager = gameMode->GetSoundManager();
	}
}


//when an enemy is alerted (in alert state), he will call this function to add the enemy to list of alerted enemies.
void AEnemyManager::AddAllertedEnemy(AEnemyAI* Enemy)
{
	AllertedEnemies.AddUnique(Enemy);
	CheckAndChangeState();
	AlertCloseEnemies(Enemy);

	//check and notify logic:
	GetSoundManager();
	if (AllertedEnemies.Num() != 0 && SoundManager)
	{
		SoundManager->bIsCombatArea = true;
		SoundManager->OnEnterCombat();
	}
}

//remove alerted enemy whenever he dies or loses sight of the player
void AEnemyManager::RemoveAllertedEnemy(AEnemyAI* Enemy)
{
	AllertedEnemies.Remove(Enemy);
	AttackingEnemies.Remove(Enemy);
	CheckAndChangeAttackState();

	GetSoundManager();
	if (AllertedEnemies.Num() == 0 && SoundManager)
	{
		SoundManager->bIsCombatArea = false;
		SoundManager->OnExitCombat();
	}
}

//make enemy go into observe state instead of attacking player, if there's already a few enemies alerted
void AEnemyManager::CheckAndChangeState()
{
	if (AllertedEnemies.Num() > 2)
	{
		// get the player's position
		ATheLandOfFeyCharacter* Player = Cast<ATheLandOfFeyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (!Player)return;
		FVector playerPos = Player->GetActorLocation();

		for (int32 i = 2; i < AllertedEnemies.Num(); i++)
		{
			if (AllertedEnemies[i] && AllertedEnemies[i]->StateManager)
			{
				// get the enemy's position
				FVector enemyPos = AllertedEnemies[i]->GetActorLocation();

				// calculate the distance between the player and the enemy
				float dist = FVector::Dist(playerPos, enemyPos);

				// only switch the state to "Observe" if the enemy is within a certain range
				if (dist <= 4000.f)
				{
					AllertedEnemies[i]->StateManager->SwitchStateByKey("Observe");
				}
				// if the enemy is out of range, consider switching it back to a non-alerted state
				else
				{
					AllertedEnemies[i]->StateManager->SwitchStateByKey("Idle");
					AllertedEnemies.RemoveAt(i);
					i--;  // Decrement counter to make up for the removed element
				}
			}
		}
	}
}

void AEnemyManager::CheckAndChangeAttackState()
{
	//while there are allerted enemies, but less than 2 attacking enemies..
	while (AttackingEnemies.Num() < 2 && AllertedEnemies.Num() > 0)
	{
		AEnemyAI* NextEnemy = AllertedEnemies[0];
		AllertedEnemies.RemoveAt(0);
		NextEnemy->StateManager->SwitchStateByKey("Combat");
		AttackingEnemies.Add(NextEnemy);

	//	if (SoundManager) 
	//	{
	//		SoundManager->bIsCombatArea = true;
	//		SoundManager->OnEnterCombat();
	//	}
	}
}

void AEnemyManager::AlertCloseEnemies(AEnemyAI* Enemy)
{
	TArray<AActor*> OverlappingEnemies;				//get all actors in radius around this enemy
	const float AlertRadius = 650.0f;				//radius for alerting other enemies
	UKismetSystemLibrary::SphereOverlapActors(Enemy->GetWorld(), Enemy->GetActorLocation(), AlertRadius, TArray<TEnumAsByte<EObjectTypeQuery>>(), AEnemyAI::StaticClass(), TArray<AActor*>(), OverlappingEnemies);			//only get actors that are of type AEnemyAI or its subclasses 

	for (AActor* HitActor : OverlappingEnemies)		//for each actor in list, if it's a enemy, alert it
	{
		AEnemyAI* EnemyToAlert = Cast<AEnemyAI>(HitActor);

		if (EnemyToAlert && EnemyToAlert != Enemy && !AllertedEnemies.Contains(EnemyToAlert))		//if enemy to alert(overlapped)
		{
			EnemyToAlert->EnemyAIController->bIsPlayerDetected = true;
			EnemyToAlert->RotateTowardsPlayer();
			EnemyToAlert->StateManager->SwitchStateByKey("Alert");									//alert enemy
			AllertedEnemies.AddUnique(EnemyToAlert);												//add them to list
		}
	}
}

void AEnemyManager::SetSoundManager(ASoundManager* SoundManagerRef)
{
	SoundManager = SoundManagerRef;
}

