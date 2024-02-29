
#include "Sound/SoundManager.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"	

// Sets default values
ASoundManager::ASoundManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Initialize your audio component variables here
    NeutralAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("NeutralAudioComponent"));
    LightAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("LightAudioComponent"));
    DarkAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("DarkAudioComponent"));

   // CombatAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("CombatAudioComponent"));
    NeutralCombatAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("NeutralCombatAudioComponent"));
    LightCombatAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("LightCombatAudioComponent"));
    DarkCombatAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("DarkCombatAudioComponent"));
    BossCombatAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BossCombatAudioComponent"));

	bIsLightArea = false;
	bIsDarkArea = false;
	bIsNeutralArea = false; 
	bIsCombatArea = false;
	bIsBossArea = false;

   // GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT("Sound manager setup"));
}

// Called when the game starts or when spawned
void ASoundManager::BeginPlay()
{
	Super::BeginPlay();

    //
    NeutralAudioComponent->bAutoActivate = false;
    LightAudioComponent->bAutoActivate = false;
    DarkAudioComponent->bAutoActivate = false;

    //com
    NeutralCombatAudioComponent->bAutoActivate = false;
    LightCombatAudioComponent->bAutoActivate = false;
    DarkCombatAudioComponent->bAutoActivate = false;
    BossCombatAudioComponent->bAutoActivate = false;

    // Play the audio components with volume 0. They'll be inaudible until you fade them in.
    if (NeutralAudioComponent) 
    {
        NeutralAudioComponent->SetVolumeMultiplier(0.0f); // Add this line
        NeutralAudioComponent->Play();
    }
    if (LightAudioComponent) 
    {
        LightAudioComponent->SetVolumeMultiplier(0.0f); // Add this line
        LightAudioComponent->Play();
    }
    if (DarkAudioComponent) 
    {
        DarkAudioComponent->SetVolumeMultiplier(0.0f); // Add this line
        DarkAudioComponent->Play();
    }

    //combat
    if (NeutralCombatAudioComponent)
    {
        NeutralCombatAudioComponent->SetVolumeMultiplier(0.0f); // Add this line
        NeutralCombatAudioComponent->Play();
    }
    if (LightCombatAudioComponent)
    {
        LightCombatAudioComponent->SetVolumeMultiplier(0.0f); // Add this line
        LightCombatAudioComponent->Play();
    }
    if (DarkCombatAudioComponent)
    {
        DarkCombatAudioComponent->SetVolumeMultiplier(0.0f); // Add this line
        DarkCombatAudioComponent->Play();
    }
    if (BossCombatAudioComponent)
    {
        BossCombatAudioComponent->SetVolumeMultiplier(0.0f); // Add this line
        BossCombatAudioComponent->Play();
    }
}

// Called every frame
void ASoundManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASoundManager::OnEnterArea() 
{
    //fade out volume for all audio components
    FadeOutAudio(NeutralAudioComponent, NeutralFadeTimerHandle);
    FadeOutAudio(LightAudioComponent, LightFadeTimerHandle);
    FadeOutAudio(DarkAudioComponent, DarkFadeTimerHandle);


    //depending on area, fade in the res audio component
    if (bIsNeutralArea)
    {
        FadeInAudio(NeutralAudioComponent, NeutralFadeTimerHandle);
    }
    else if (bIsLightArea)
    {
        FadeInAudio(LightAudioComponent, LightFadeTimerHandle);
    }
    else if (bIsDarkArea)
    {
        FadeInAudio(DarkAudioComponent, DarkFadeTimerHandle);
    }

}


void ASoundManager::FadeOutAudio(UAudioComponent* AudioComponent, FTimerHandle& FadeTimerHandle)
{
    if (!AudioComponent)
        return;

    FTimerDelegate TimerDel;
    TimerDel.BindLambda([this, AudioComponent, &FadeTimerHandle]
        {
            float CurrentVolume = AudioComponent->VolumeMultiplier;

    if (CurrentVolume > 0.0f)
    {
        AudioComponent->SetVolumeMultiplier(FMath::Max(0.0f, CurrentVolume - 0.005f));
    }
    else
    {
        GetWorldTimerManager().ClearTimer(FadeTimerHandle);
    }
        });

    GetWorldTimerManager().SetTimer(FadeTimerHandle, TimerDel, 0.02f, true, 0.0f);      //decrease volume by small amount each 0.02 seconds until volume 0
}


void ASoundManager::FadeInAudio(UAudioComponent* AudioComponent, FTimerHandle& FadeTimerHandle)
{
    if (!AudioComponent)
        return;

   
    AudioComponent->SetVolumeMultiplier(0.0f);                                               //set volume to 0

    //delegate
    FTimerDelegate TimerDel;                                                                //create delegate for timer

    TimerDel.BindLambda([this, AudioComponent, &FadeTimerHandle]                            //bind lambda to delegate
        {
            float CurrentVolume = AudioComponent->VolumeMultiplier;                         //get current volume

    if (CurrentVolume < 1.0f)                                                               //if volume isnt max volume
    {
        AudioComponent->SetVolumeMultiplier(FMath::Min(1.0f, CurrentVolume + 0.005f));       //increae volume by small amount depending on desired fade speed
    }
    else
    {
        GetWorldTimerManager().ClearTimer(FadeTimerHandle);                                 //clear timer
    }
        });
    //delegate

    GetWorldTimerManager().SetTimer(FadeTimerHandle, TimerDel, 0.02f, true, 0.0f);          //set timer to run every 0.2 seconds calling delegate each time
}

void ASoundManager::OnEnterCombat()
{
    if (bIsBossArea)
    {
        CurrentCombatAudioComponent = BossCombatAudioComponent;
     //   CurrentFadeTimerHandle = BossCombatFadeTimerHandle;
        FadeInAudio(BossCombatAudioComponent, BossCombatFadeTimerHandle);
        // rest of your code...
    }
    else if (bIsNeutralArea)
    {
        CurrentCombatAudioComponent = NeutralCombatAudioComponent;
     //   CurrentFadeTimerHandle = NeutralCombatFadeTimerHandle;
        FadeInAudio(NeutralCombatAudioComponent, NeutralCombatFadeTimerHandle);
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT("Sound manager: NEUTRAL COMBAT MUSIC START"));
    }
    else if (bIsLightArea)
    {
        CurrentCombatAudioComponent = LightCombatAudioComponent;
     //   CurrentFadeTimerHandle = LightFadeTimerHandle;
        FadeInAudio(LightCombatAudioComponent, LightCombatFadeTimerHandle);
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT("Sound manager: LIGHT COMBAT MUSIC START"));
    }
    else if (bIsDarkArea)
    {
        CurrentCombatAudioComponent = DarkCombatAudioComponent;
       // CurrentFadeTimerHandle = DarkFadeTimerHandle;
        FadeInAudio(DarkCombatAudioComponent, DarkCombatFadeTimerHandle);
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT("Sound manager: DARK COMBAT MUSIC START"));
    }
}

void ASoundManager::OnExitCombat()
{
    if (bIsBossArea)
    {
        FadeOutAudio(BossCombatAudioComponent, BossCombatFadeTimerHandle);
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT("Sound manager: BOSS COMBAT MUSIC START"));
    }
    else if (bIsNeutralArea)
    {
        FadeOutAudio(NeutralCombatAudioComponent, NeutralCombatFadeTimerHandle);
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT("Sound manager: NEUTRAL COMBAT MUSIC START"));
    }
    else if (bIsLightArea)
    {
        FadeOutAudio(LightCombatAudioComponent, LightCombatFadeTimerHandle);
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT("Sound manager: LIGHT COMBAT MUSIC START"));
    }
    else if (bIsDarkArea)
    {
        FadeOutAudio(DarkCombatAudioComponent, DarkCombatFadeTimerHandle);
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT("Sound manager: DARK COMBAT MUSIC START"));
    }

   // if (CurrentCombatAudioComponent)
   // {
   //     FadeOutAudio(CurrentCombatAudioComponent, CurrentFadeTimerHandle);
   // }
   ///* else if (bIsBossArea)
   // {
   // FadeOutAudio(BossCombatAudioComponent, BossCombatFadeTimerHandle);
   // GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT("Sound manager: BOSS COMBAT MUSIC START"));
   // }
   // else if (bIsNeutralArea)
   // {
   //     FadeOutAudio(NeutralCombatAudioComponent, NeutralCombatFadeTimerHandle);
   //     GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT("Sound manager: NEUTRAL COMBAT MUSIC START"));
   // }
   // else if (bIsLightArea)
   // {
   //     FadeOutAudio(LightCombatAudioComponent, LightCombatFadeTimerHandle);
   //     GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT("Sound manager: LIGHT COMBAT MUSIC START"));
   // }
   // else if (bIsDarkArea)
   // {
   //     FadeOutAudio(DarkCombatAudioComponent, DarkCombatFadeTimerHandle);
   //     GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, TEXT("Sound manager: DARK COMBAT MUSIC START"));
   // }*/
}