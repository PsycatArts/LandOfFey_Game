#pragma once

#include "CoreMinimal.h"
#include "Enemy/States/EnemyStateBase.h"
#include "EnemyStateAbility.generated.h"

UCLASS()
class THELANDOFFEY_API UEnemyStateAbility : public UEnemyStateBase
{
	GENERATED_BODY()

protected:
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void TickState() override;
	virtual void OnExitState() override;

	void BackToCombatWrapper();



	UPROPERTY(EditAnywhere, BlueprintReadWrite)			//how long the character animation takes / when to exit ability state
	float AbilityDuration = 2.5f;



	void ChooseAbility();

	//---DARK FOG CLOUD---
	void DarkAbility();
	void SpawnFog();
	void DestroyFog();


	void MoveAwayFromPlayer();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Dark Ability ")		//var to assign the montage
		UAnimMontage* DarkAbility_Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Dark Ability ")
	float DestroyFogTime = 4.f;


	UPROPERTY(EditAnywhere, Category = " Dark Ability ")
	TSubclassOf<AActor> DarkAbility_ToSpawn;

	AActor* SpawnedFogActor = nullptr;

	FTimerHandle MoveAwayTimer;
	FTimerHandle FogTimerHandle;
	FTimerHandle FogSpawnTimerHandle;
	


	//---LIGHT CRYSTAL PROJECTILE---
	void LightAbility();
	void SpawnProjectile();
	void DestroyProjectile();

	AActor* SpawnedProjectileActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Light Ability ")		//var to assign the montage
		UAnimMontage* LightAbility_Montage;
	
	UPROPERTY(EditAnywhere, Category = " Light Ability ")															//Crystal projectile blueprint actor to spawn 
	TSubclassOf<AActor> CrystalToSpawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = " Light Ability ")										//distance that enemy needs to have between him and player, so that projectile will be shot from distance
	float MinProjectileDistance = 550.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = " Light Ability ")		//time after which projectile is spawned.. after 1 sec into animation
	float ProjectileSpawnAfter = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = " Light Ability ")		//time after which projectile will be destroyed
	float DestroyProjectileTime = 4.f;
	
	FTimerHandle CrystalTimerHandle;																					//keep track of when to spawn crsyal
	FTimerHandle AbilityResetTimerHandle;




	
};
