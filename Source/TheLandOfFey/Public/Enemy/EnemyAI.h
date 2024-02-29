#pragma once

#include "CoreMinimal.h"
#include "CombatHitInterface.h"
#include "GameFramework/Character.h"
#include "StateManagerComponent.h"
#include "ElementalAbilityComponent.h"
#include "Enemy/EnemyManager.h"
#include "EnemyAI.generated.h"


class AEnemyAIController;										//forward declaration
//class AEnemyManger;										//forward declaration


UCLASS()
class THELANDOFFEY_API AEnemyAI : public ACharacter, public ICombatHitInterface
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	// Sets default values for this character's properties
	AEnemyAI();

	//override combathit interface
	virtual void CombatHit_Implementation(FHitResult HitResult) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateMachine")
	UStateManagerComponent* StateManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Element")
	UElementalAbilityComponent* ElementSystem;

	UPROPERTY()
	AEnemyAIController* EnemyAIController;

	UPROPERTY(BlueprintReadWrite)
	AEnemyManager* EnemyManager;


	void RotateTowardsPlayer();



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float BaseDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool IsHurting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool IsDead;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	bool IsAttacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool IsTargeted;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	//bool IsAllerted;


	//getters for BaseDamage to be callable in Enemy Child classes etc.. To acoid making Health var public
	FORCEINLINE float GetDamage() const { return BaseDamage; }
	//FORCEINLINE float GetAbilityDamage() const { return AbilityDamage; }

	FORCEINLINE bool GetIsDead() const { return IsDead; }
	FORCEINLINE float GetHealth() const { return Health; }


};
