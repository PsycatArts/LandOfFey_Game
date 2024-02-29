
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "SoundManager.generated.h"

UCLASS()
class THELANDOFFEY_API ASoundManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//---ATMOS---
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* NeutralAudioComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* LightAudioComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* DarkAudioComponent;


	//---COMBAT---

	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* CombatAudioComponent;*/

	UAudioComponent* CurrentCombatAudioComponent;				//to hold ref of currently playing combat audio

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* NeutralCombatAudioComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* LightCombatAudioComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* DarkCombatAudioComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* BossCombatAudioComponent;



	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Area", meta = (AllowPrivateAccess = "true"))
		bool bIsLightArea;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Area", meta = (AllowPrivateAccess = "true"))
		bool bIsDarkArea;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Area", meta = (AllowPrivateAccess = "true"))
		bool bIsNeutralArea;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Area", meta = (AllowPrivateAccess = "true"))
		bool bIsCombatArea;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Area", meta = (AllowPrivateAccess = "true"))
		bool bIsBossArea;

	UFUNCTION(BlueprintCallable)
	void OnEnterArea();

	UFUNCTION(BlueprintCallable)
		void OnEnterCombat();

	UFUNCTION(BlueprintCallable)
		void OnExitCombat();

	// Timer handles for fading processes
	FTimerHandle NeutralFadeTimerHandle;
	FTimerHandle LightFadeTimerHandle;
	FTimerHandle DarkFadeTimerHandle;
//	FTimerHandle CombatFadeTimerHandle;
	FTimerHandle CurrentFadeTimerHandle;
	FTimerHandle NeutralCombatFadeTimerHandle;
	FTimerHandle LightCombatFadeTimerHandle;
	FTimerHandle DarkCombatFadeTimerHandle;
	FTimerHandle BossCombatFadeTimerHandle;

	void FadeOutAudio(UAudioComponent* AudioComponent, FTimerHandle& FadeTimerHandle);
	void FadeInAudio(UAudioComponent* AudioComponent, FTimerHandle& FadeTimerHandle);

};
