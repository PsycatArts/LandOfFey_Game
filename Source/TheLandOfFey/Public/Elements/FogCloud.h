// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "ElementalAbilityComponent.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "FogCloud.generated.h"

UCLASS()
class THELANDOFFEY_API AFogCloud : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFogCloud();

	// Destructor
	//virtual ~AFogCloud();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	bool IsPlayerOutside();

	bool IsOutside;
	void SpawnPreview();
	void SpawnFogCloud();
	void ApplyFogDamage();

	
//	AActor* PlayerActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UElementalAbilityComponent* ElementSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* SphereCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FogCloud_Damage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)					//the preview VFX which is spawned before actual FogCloudVFX
	class UNiagaraSystem* NiagaraParticle_FogPreview;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)					//actual FogCloudVFX
	class UNiagaraSystem* NiagaraParticle_FogCloud;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)					//impact VFX when hitting player
	class UNiagaraSystem* NiagaraParticle_Impact_Dark;

	UFUNCTION(BlueprintImplementableEvent)				//sound when player presses attack
	void Fog_SFX();
	 
	//Sphere collider overlap
	UFUNCTION()
		void OnFogCloudEnter(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult
		);


	FTimerHandle FogCloudTimerHandle;
	FTimerHandle DamageTimerHandle;

	//UFUNCTION()
	//	void OnFogCloudExit(
	//		UPrimitiveComponent* OverlappedComponent,
	//		AActor* OtherActor,
	//		UPrimitiveComponent* OtherComp,
	//		int32 OtherBodyIndex
	//	);

};
