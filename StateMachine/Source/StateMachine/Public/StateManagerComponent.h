#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateBase.h"
#include "StateManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STATEMACHINE_API UStateManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStateManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "State Machine")
	FString InitialState;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "State Machine")																		//list of all states that are possible to use
	TMap < FString, TSubclassOf<UStateBase>> AvailableStates;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "State Machine Debug")
	bool bDebug = false;
	
	UPROPERTY(BlueprintReadOnly)																													//previous state
	TArray<UStateBase*> StateHistory;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "State Machine Debug", meta= (ClampMin="0", ClampMax="10", UIMin="0", UIMax="10"))
	int32 StateHistoryLength;

	UPROPERTY(BlueprintReadOnly)
	UStateBase* CurrentState = nullptr;

	UPROPERTY()
	TMap <FString, UStateBase*> StateMap;


	UFUNCTION(BlueprintCallable, Category = "State Machine")
	void SwitchStateByKey(FString StateKey);


	FORCEINLINE UStateBase* GetCurrentS() const { return CurrentState; }

	//UFUNCTION(BlueprintCallable, Category = "State Machine")
	//UStateBase GetCurrentState(FString StateKey);

	//UFUNCTION(BlueprintCallable, Category = "State Machine")
	//void SwitchState(UStateBase* NewState);
	
	UFUNCTION(BlueprintCallable, Category = "State Machine")				//called on begin play to handle initialisation
	void InitStateManager();

private:
	bool bCanTickState = false;
	void InitializeStates();
};
