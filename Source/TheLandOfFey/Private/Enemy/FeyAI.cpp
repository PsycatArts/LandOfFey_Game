// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/FeyAI.h"
#include "TheLandOfFey/TheLandOfFeyCharacter.h"
#include "Enemy/EnemyAIController.h"
#include "Enemy/EnemyManager.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "Kismet/GameplayStatics.h"	
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"

AFeyAI::AFeyAI()
{
	PrimaryActorTick.bCanEverTick = true;

	//ORIENT ROTATION TO MOVEMENT
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.0f, 0.0f);

	//WEAPON BOX COLLISION
	WeaponCollisionR = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Box Right"));
	WeaponCollisionR->SetupAttachment(GetMesh(), FName("WeaponSocketR"));

	WeaponCollisionL = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Box Left"));
	WeaponCollisionL->SetupAttachment(GetMesh(), FName("WeaponSocketL"));

	IsAttacking = false;
}

void AFeyAI::BeginPlay()
{
	Super::BeginPlay();

	AI_Controller = Cast<AEnemyAIController>(GetController());

	//WEAPON BOX COLLISIONS
	WeaponCollisionR->OnComponentBeginOverlap.AddDynamic(this, &AFeyAI::OnWeaponOverlap);				// bind function to overlap event for WeaponCollision;		(delegate)		
	WeaponCollisionL->OnComponentBeginOverlap.AddDynamic(this, &AFeyAI::OnWeaponOverlap);				// bind function to overlap event for WeaponCollision;		

	WeaponCollisionR->SetCollisionEnabled(ECollisionEnabled::NoCollision);											//setup weapon collision box
	WeaponCollisionR->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	WeaponCollisionR->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponCollisionR->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	WeaponCollisionL->SetCollisionEnabled(ECollisionEnabled::NoCollision);											//setup weapon collision box
	WeaponCollisionL->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	WeaponCollisionL->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponCollisionL->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	

	//StateManager->SwitchStateByKey("Idle");
}

void AFeyAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AFeyAI::OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr) return;		//if no actor was hit, dont do anything

	ATheLandOfFeyCharacter* Player = Cast<ATheLandOfFeyCharacter>(OtherActor);

	if (Player)
	{
		UGameplayStatics::ApplyDamage(Player,GetDamage() /** DamageMultiplier*/, EnemyAIController, this, UDamageType::StaticClass() );
	}
}


//void AFeyAI::Knockback(FVector SourceLocation, float Strength)
//{
//	FVector KnockbackDirection = this->GetActorLocation() - SourceLocation;
//	KnockbackDirection.Normalize();													//normalize/ensure direction vector has a length of 1
//	KnockbackDirection.Z = 0.5f;													//upward force
//	LaunchCharacter(KnockbackDirection * Strength, true, true);
//	//anim
//	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
//	if (AnimInstance && KnockbackMontage)
//	{
//		AnimInstance->Montage_Play(KnockbackMontage);
//	}
//}


// weapon collision ----
void AFeyAI::ActivateWeaponR()
{
	WeaponCollisionR->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AFeyAI::DeactivateWeaponR()
{
	WeaponCollisionR->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AFeyAI::ActivateWeaponL()
{
	WeaponCollisionL->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AFeyAI::DeactivateWeaponL()
{
	WeaponCollisionL->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

