#include "Enemy/EnemyAI.h"
#include "Enemy/EnemyAIController.h"
#include "TheLandOfFey/TheLandOfFeyCharacter.h"
#include "TheLandOfFey/TheLandOfFeyGameMode.h"
#include "Kismet/GameplayStatics.h"	

AEnemyAI::AEnemyAI()
{
	PrimaryActorTick.bCanEverTick = true;

	StateManager = CreateDefaultSubobject<UStateManagerComponent>(TEXT("StateManager"));
	ElementSystem = CreateDefaultSubobject<UElementalAbilityComponent>(TEXT("ElementManager"));

	IsDead = false;
	IsHurting = false;
	IsAttacking = false;
	IsTargeted = false;
}

void AEnemyAI::BeginPlay()
{
	Super::BeginPlay();
	
	EnemyAIController = Cast<AEnemyAIController>(GetController());
	StateManager->InitStateManager();
	ElementSystem->InitElementManager();
	
	ATheLandOfFeyGameMode* GameMode = Cast<ATheLandOfFeyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));			//enemy manager setup
	if (GameMode != nullptr)
	{
		EnemyManager = GameMode->EnemyManagerInstance;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Game mode or Enemy Manager Instance not found"));
	}
}

void AEnemyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyAI::RotateTowardsPlayer()
{
	if (!IsDead)
	{
		ATheLandOfFeyCharacter* Player = Cast<ATheLandOfFeyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (!Player)return;

		//direction of player
		FVector Direction = Player->GetActorLocation() - this->GetActorLocation();
		Direction.Normalize();
		FRotator CurrentRotation = this->GetActorRotation();

		//rotate enemy towards the player
		FRotator TargetRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
		this->SetActorRotation(FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), 55.f));
	}
}

float AEnemyAI::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	ATheLandOfFeyCharacter* AttackerPlayer = Cast<ATheLandOfFeyCharacter>(DamageCauser);							//attacker is player

	float DamageMultiplier = 1.0f;																					//default to normal damage

	FName AttackerElementName;																						//variables to store  element names
	FName DefenderElementName;

	
	if (this->ElementSystem && this->ElementSystem->GetCurrentElement())											//get defenders element name (this enemy element)
	{
		DefenderElementName = this->ElementSystem->GetCurrentElement()->ElementDisplayName;
	}


	if (AttackerPlayer && AttackerPlayer->ElementSystem && AttackerPlayer->ElementSystem->GetCurrentElement())		//get Attackers (Players) element
	{
		AttackerElementName = AttackerPlayer->ElementSystem->GetCurrentElement()->ElementDisplayName;
	}

	
	TPair<FName, FName> ElementPair = TPair<FName, FName>{ DefenderElementName, AttackerElementName };				//get damage multiplier from the matrix
	if (ElementSystem && ElementSystem->ElementalDamageMatrix.Contains(ElementPair))
	{
		DamageMultiplier = ElementSystem->ElementalDamageMatrix[ElementPair];
	}

	Health -= DamageAmount * DamageMultiplier;

	if (Health <= 0.f)
	{
		if (!IsDead)
		{
			StateManager->SwitchStateByKey("Death");
		}
	}
	else
	{
		StateManager->SwitchStateByKey("Hurt");
	}

	return DamageAmount * DamageMultiplier;
}

void AEnemyAI::CombatHit_Implementation(FHitResult HitResult)
{
	//sfx vfx
	//ATheLandOfFeyCharacter* Player = Cast<ATheLandOfFeyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//if (Player == nullptr)
	//	return;
	//if (Player->ElementSystem->CurrentElement) 
	//{
	//	if (Player->ElementSystem->CurrentElement->ElementDisplayName == "Light")
	//	{
	//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("ENEMY AI:: I WAS HIT BY A LIGHT ELEMENT"));
	//	} 
	//	else if (Player->ElementSystem->CurrentElement->ElementDisplayName == "Dark") 
	//	{
	//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("ENEMY AI:: I WAS HIT BY A DARK ELEMENT"));
	//	}
	//}
	//else 
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("ENEMY AI:: I WAS HIT BY NO ELEMENT"));
	//}
}





