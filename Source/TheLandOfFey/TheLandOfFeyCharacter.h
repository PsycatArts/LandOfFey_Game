// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
//#include "../Plugins/StateMachine/Source/StateMachine/public/StateMachine.h"
#include "StateManagerComponent.h"
//#include "../../Plugins/ElementalAbilitySystem/Source/ElementalAbilitySystem/Public/ElementalAbilityComponent.h"
#include "ElementalAbilityComponent.h"
#include "Enemy/CombatHitInterface.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "TheLandOfFeyCharacter.generated.h"



UCLASS(config=Game)
class ATheLandOfFeyCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;
	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;


	/** Attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MainAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* RightClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SwitchElementAction;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	//bool IsJumping;



public:
	ATheLandOfFeyCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateMachine")
	UStateManagerComponent* StateManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Element")
	UElementalAbilityComponent* ElementSystem;



	//ATTACK
	void MainAttack();



	//not used atm, but works
	void Stun();

	void AbilityAttack();

	void SwitchElement();

	void ResetCanUseSwitch();



	UFUNCTION(BlueprintCallable)
	void StartDodge();

	// Variables to track dodge movement
	FVector DodgeDirection;
	bool IsDodging;

	bool Invincible;

	bool IsHurting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool IsTargetLocking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool Stunned;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float BaseDamage = 6.f;	

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	//float SwitchCooldown= 2.f;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	//bool CanUseSwitch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		float SwitchCooldownMax = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		float SwitchCooldownRemaining = 0.f;

	FTimerHandle SwitchCooldownTimer;
	FTimerHandle SwitchCooldownUpdateTimer;

	void UpdateSwitchCooldown();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float Health;		

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float MaxHealth;		

	//PREVENT BUTTON SPAMMING and determine when attacking for further usage in vfx etc
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool IsAttacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool IsDead;


	//SOUND EFFECTS

	UFUNCTION(BlueprintImplementableEvent)				//sound when player presses attack
	void Melee_SFX();

	UFUNCTION(BlueprintImplementableEvent)				//sound when player HIT the enemy
	void Melee_Hit_SFX();

	UFUNCTION(BlueprintImplementableEvent)				//sound when player switches element
	void SwitchElement_SFX();

	UFUNCTION(BlueprintImplementableEvent)				//sound when player dodges
	void Dodge_SFX();

	//getting a screenshake in BP 
	UFUNCTION( BlueprintImplementableEvent)
	void Hurt_VFX();

	UFUNCTION(BlueprintImplementableEvent)
	void HittingEnemy_VFX();


	//ATTACK BOX COLLISION
	virtual void ActivateWeapon();											//activate and deactivate WeaponCollisionBox
	virtual void DeactivateWeapon();

	//USED IN DODGE ANIM
	void Activate_I_Frames();
	void Deactivate_I_Frames();

	//BOX OVERLAP (to detect if enemy was hit)
	UFUNCTION()
		void OnWeaponOverlap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult
		);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	UBoxComponent* RightWeaponCollision;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();
	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

};

