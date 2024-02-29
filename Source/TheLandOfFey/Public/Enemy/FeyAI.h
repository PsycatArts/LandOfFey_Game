// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyAI.h"
//#include "Enemy/EnemyManager.h"
#include "Components/BoxComponent.h"
#include "FeyAI.generated.h"

class UAnimMontage;																		//forward declaration
class AEnemyAIController;																		//forward declaration

/**
 * 
 */
UCLASS()
class THELANDOFFEY_API AFeyAI : public AEnemyAI
{
	GENERATED_BODY()

public:
	AFeyAI();

	UPROPERTY()
	AEnemyAIController* AI_Controller;

	//Weapon collision
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	UBoxComponent* WeaponCollisionR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	
	UBoxComponent* WeaponCollisionL;

	UFUNCTION()
	void OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,
		UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);

	virtual void ActivateWeaponR();											
	virtual void DeactivateWeaponR();

	virtual void ActivateWeaponL();
	virtual void DeactivateWeaponL();


	UFUNCTION(BlueprintImplementableEvent)				//BP function to fade and destroy on death
	void Death_Fade();

	UFUNCTION(BlueprintImplementableEvent)				//BP function to apply shader when hit
	void Hurt_Shader();

	UFUNCTION(BlueprintImplementableEvent)				//sound when player presses attack
	void Melee_SFX();

	UFUNCTION(BlueprintImplementableEvent)				//sound when player presses attack
	void Melee_Grunt_SFX();
	
	UFUNCTION(BlueprintImplementableEvent)				//sound when player presses attack
	void Knockback_SFX();

	UFUNCTION(BlueprintImplementableEvent)				
	void Hurt_SFX();

	UFUNCTION(BlueprintImplementableEvent)				
	void Death_SFX();

	UFUNCTION(BlueprintImplementableEvent)				
	void Idle_SFX();

	UFUNCTION(BlueprintImplementableEvent)
	void Alert_SFX();

	UFUNCTION(BlueprintImplementableEvent)
		void LightAbility_Windup_SFX();

	UFUNCTION(BlueprintImplementableEvent)
		void DarkAbility_Windup_SFX();

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;


	
};
