// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheLandOfFeyCharacter.h"
#include "Enemy/CombatHitInterface.h"
#include "Enemy/EnemyAI.h"
#include "ElementBase.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


//////////////////////////////////////////////////////////////////////////
// ATheLandOfFeyCharacter

ATheLandOfFeyCharacter::ATheLandOfFeyCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	//WEAPON BOX COLLISION
	RightWeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Box Right"));
	RightWeaponCollision->SetupAttachment(GetMesh(), FName("WeaponSocketR"));

	//STATE MACHINE
	StateManager = CreateDefaultSubobject<UStateManagerComponent>(TEXT("StateManager"));

	ElementSystem = CreateDefaultSubobject<UElementalAbilityComponent>(TEXT("ElementManager"));

	Health = 100.f;
	MaxHealth = 100.f;
	Stunned = false;
	IsDead = false;
	//CanUseSwitch = true;
	IsHurting = false;
	Invincible = false;
	IsDodging = false;
	IsTargetLocking = false;
}


void ATheLandOfFeyCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	StateManager->InitStateManager();
	ElementSystem->InitElementManager();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	//WEAPON BOX COLLISION 
	RightWeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &ATheLandOfFeyCharacter::OnWeaponOverlap);				// bind function to overlap event for WeaponCollision

	RightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);												//setup weapon collision box
	RightWeaponCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	RightWeaponCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	RightWeaponCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);	
}

// Input
void ATheLandOfFeyCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATheLandOfFeyCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATheLandOfFeyCharacter::Look);

		//Attacking
		EnhancedInputComponent->BindAction(MainAttackAction, ETriggerEvent::Started, this, &ATheLandOfFeyCharacter::MainAttack);

		EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Started, this, &ATheLandOfFeyCharacter::AbilityAttack);
		EnhancedInputComponent->BindAction(SwitchElementAction, ETriggerEvent::Started, this, &ATheLandOfFeyCharacter::SwitchElement);

		//dodging
		//PlayerInputComponent->BindAxis("MovingForward", this, &ATheLandOfFeyCharacter::MovingForward);
		//PlayerInputComponent->BindAxis("MovingRight", this, &ATheLandOfFeyCharacter::MovingRight);

	}
}

void ATheLandOfFeyCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);

		//dodge
		DodgeDirection = FVector(MovementVector.Y, MovementVector.X, 0).GetSafeNormal();
	}
}

void ATheLandOfFeyCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}


float ATheLandOfFeyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!IsDead && !Invincible)
	{
		AEnemyAI* Attacker = Cast<AEnemyAI>(DamageCauser);									//attacker is enemy

		float DamageMultiplier = 1.0f;														//default to normal damage
		
		FName AttackerElementName;															//variables to store  element names
		FName DefenderElementName;
		
		if (this->ElementSystem && this->ElementSystem->GetCurrentElement())				//get defenders (Player) element 
		{
			DefenderElementName = this->ElementSystem->GetCurrentElement()->ElementDisplayName;
		}
		
		if (Attacker && Attacker->ElementSystem && Attacker->ElementSystem->GetCurrentElement())	//Get Attackers (enemy) element name
		{
			AttackerElementName = Attacker->ElementSystem->GetCurrentElement()->ElementDisplayName;
		}

		
		TPair<FName, FName> ElementPair = TPair<FName, FName>{ DefenderElementName, AttackerElementName };		//get damage multiplier from the matrix
		if (ElementSystem && ElementSystem->ElementalDamageMatrix.Contains(ElementPair))
		{
			DamageMultiplier = ElementSystem->ElementalDamageMatrix[ElementPair];
		}


		Hurt_VFX();
		Health -= DamageAmount * DamageMultiplier;

		if (Health <= 0.f)
		{
			IsDead = true;
			//StateManager->SwitchStateByKey("Death");
		}
		else
		{
			StateManager->SwitchStateByKey("Hurt");
		}

		return DamageAmount * DamageMultiplier;
	}

	return 0.f;
}


void ATheLandOfFeyCharacter::MainAttack()
{
	StateManager->SwitchStateByKey("Attacking");
}

void ATheLandOfFeyCharacter::Stun()
{
	StateManager->SwitchStateByKey("Stun");
}

//is now done in BP
void ATheLandOfFeyCharacter::AbilityAttack()
{
	//if (CanUseAbility)
	//{
	//	StateManager->SwitchStateByKey("AbilityA");
	//	CanUseAbility = false;
	//	GetWorldTimerManager().SetTimer(AbilityCooldownTimer, this, &ATheLandOfFeyCharacter::ResetCanUseAbility, AbilityCooldown, false);
	//}
}

void ATheLandOfFeyCharacter::ResetCanUseSwitch() 
{
	//CanUseSwitch = true;

	// Instead of a bool, we set the remaining cooldown to 0 when it's done
	SwitchCooldownRemaining = 0.f;

	// Stop the update timer when the cooldown is done
	GetWorldTimerManager().ClearTimer(SwitchCooldownUpdateTimer);
}

void ATheLandOfFeyCharacter::UpdateSwitchCooldown()
{
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	SwitchCooldownRemaining = FMath::Max(0.f, SwitchCooldownRemaining - DeltaTime);		//reduce cooldown until 0
}

void ATheLandOfFeyCharacter::SwitchElement()
{
	// Check if cooldown has expired
	if (SwitchCooldownRemaining <= 0.f)
	{
		StateManager->SwitchStateByKey("SwitchElement");

		// Set the remaining cooldown to the max cooldown value
		SwitchCooldownRemaining = SwitchCooldownMax;

		// Set the timer to call ResetCanUseSwitch after the cooldown expires
		GetWorldTimerManager().SetTimer(SwitchCooldownTimer, this, &ATheLandOfFeyCharacter::ResetCanUseSwitch, SwitchCooldownMax, false);

		// Start an update timer that calls UpdateSwitchCooldown every 0.1 seconds (or a smaller value if you want smoother UI updates)
		GetWorldTimerManager().SetTimer(SwitchCooldownUpdateTimer, this, &ATheLandOfFeyCharacter::UpdateSwitchCooldown, 0.01f, true);
	}

	////use if cooldown allows
	//if (CanUseSwitch)
	//{
	//	StateManager->SwitchStateByKey("SwitchElement");
	//	CanUseSwitch = false;
	//	GetWorldTimerManager().SetTimer(SwitchCooldownTimer, this, &ATheLandOfFeyCharacter::ResetCanUseSwitch, SwitchCooldown, false);
	//}
}

//----OVERLAP OF ATTACK COLLISION----//
void ATheLandOfFeyCharacter::OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//CKECK IF SWEEPRESULT HIT AN ACTOR
	if (IsValid(SweepResult.GetActor()))
	{
		if (SweepResult.GetActor() != this)
		{
			//--BP function to spawn VFX and camera shake--
			HittingEnemy_VFX();
			Melee_Hit_SFX();

			// call combatHitInterface fct of enemy.. (knockback etc)
			ICombatHitInterface* HitInterface = Cast<ICombatHitInterface>(SweepResult.GetActor());
			if (HitInterface)
			{
				HitInterface->CombatHit_Implementation(SweepResult);
			}

			//apply damage
			UGameplayStatics::ApplyDamage(																			//standard BP node "ApplyDamage"
				SweepResult.GetActor(),																				//get actor that's been hit
				BaseDamage,																							//damage amount to be applied
				GetController(),
				this,
				UDamageType::StaticClass());
		}
	}
}

//called in BP when pressing LEFT SHIFT
void ATheLandOfFeyCharacter::StartDodge()
{
	StateManager->SwitchStateByKey("Dodge");
}

//----ATTACK BOX COLLISION----// called in notifier
void ATheLandOfFeyCharacter::ActivateWeapon()
{
	RightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ATheLandOfFeyCharacter::DeactivateWeapon()
{
	RightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ATheLandOfFeyCharacter::Activate_I_Frames()
{
	Invincible = true;
	
}

void ATheLandOfFeyCharacter::Deactivate_I_Frames()
{
	Invincible = false;
}
