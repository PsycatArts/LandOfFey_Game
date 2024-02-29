// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/FeyStateBase.h"
#include "FeyStateAbilityA.generated.h"

/**
 * 
 */
UCLASS()
class THELANDOFFEY_API UFeyStateAbilityA : public UFeyStateBase
{
	GENERATED_BODY()
protected:
	virtual void TickState() override;
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void OnExitState() override;


	//--DARK: Fog cloud ability
	void UseAbility();
	void SpawnFog();

	void BackToCombat();

	void DestroyObject();
	void MoveAwayFromPlayer();

	FTimerHandle MoveAwayTimer;

	//animation to playe on character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Fog Cloud")		//var to assign the montage
	UAnimMontage* FogCloud_Ability_Montage;

	//how long the character animation takes / when to exit ability state
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float AbilityDuration= 2.5f;

	//how long it takes until fog object gets destroyed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = " Fog Cloud")
	float DestroyFogTime = 4.f;

	//Fog blueprint actor to spawn 
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = " Fog Cloud")
	TSubclassOf<AActor> FogToSpawn;



	AActor* SpawnedFogActor = nullptr;

	FTimerHandle FogTimerHandle;
	FTimerHandle FogSpawnTimerHandle;
	FTimerHandle AbilityResetTimerHandle;



	//--LIGHT: Crystal Projectile

	//Crystal blueprint actor to spawn 
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = " Projectile")
	TSubclassOf<AActor> CrystalToSpawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = " Projectile")
	float MinProjectileDistance = 550.0f;


	AActor* SpawnedProjectileActor = nullptr;

	void UseProjectile();
	void SpawnProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = " Projectile")
	float ProjectileSpawnAfter = 1.f;

	//keep track of when to spawn crsyal
	FTimerHandle CrystalTimerHandle;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Fog Cloud")		//var to assign the montage
	//UAnimMontage* Projectile_Ability_Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = " Projectile")
	float DestroyProjectileTime = 4.f;
	
};
