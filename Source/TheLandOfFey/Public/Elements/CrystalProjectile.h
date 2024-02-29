#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "ElementalAbilityComponent.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "CrystalProjectile.generated.h"

UCLASS()
class THELANDOFFEY_API ACrystalProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ACrystalProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UElementalAbilityComponent* ElementSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CrystalCapsuleCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Projectile_Damage= 10.f;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* NiagaraParticle_Light;

	UFUNCTION(BlueprintImplementableEvent)				//sound when player presses attack
	void Shoot_SFX();

	UFUNCTION(BlueprintImplementableEvent)				//sound when player presses attack
	void Impact_SFX();

	//Sphere collider overlap
	UFUNCTION()
		void OnProjectileHit(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult
		);

};
