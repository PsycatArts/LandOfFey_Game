#include "StateManagerComponent.h"
#include "StateMachine/Public/StateManagerComponent.h"


UStateManagerComponent::UStateManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UStateManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeStates();
}


// Called every frame
void UStateManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bCanTickState) 
	{
		CurrentState->TickState();
	}
	if (bDebug) 
	{
		if (CurrentState)
			GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Green, this->GetOwner()->GetName() + "'s current state: " + CurrentState->StateDisplayName.GetPlainNameString());
		if (StateHistory.Num() > 0)
		{
			/*
			//Output the past state
			for (int32 i = 0; i < StateHistory.Num(); i++)
			{
				GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Purple, this->GetOwner()->GetName() + "'s past state " + FString::FromInt(i) + " " + StateHistory[i]->GetName());
			}*/
		}
	}
}

void UStateManagerComponent::SwitchStateByKey(FString StateKey)
{
	if (!StateMap.Contains(StateKey))
	{
		if (bDebug)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, this->GetOwner()->GetName() + "'s state switch failed: Invalid StateKey");
		}
		return;
	}

	//create new var that holds value of StateKey given in parameter
	UStateBase* NewState = StateMap[StateKey];

	//error validation
	if (NewState->IsValidLowLevel())
	{
		//If there is no current state, it means we are at initialising it first time
		if (!CurrentState)
		{
			//set current state to the new one given
			CurrentState = NewState;
			CurrentState->OnEnterState(GetOwner());
			bCanTickState = true;
		}
		else
		{
			if (CurrentState->GetClass() == NewState->GetClass() && CurrentState->bCanRepeat == false)
			{
				if (bDebug)
				{
					GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, this->GetOwner()->GetName() + "'s state switch failed. " + CurrentState->StateDisplayName.GetPlainNameString() + " is not repeatable!", true);
				}
			}
			else
			{
				//if there already is a state, exit that one
				bCanTickState = false;
				CurrentState->OnExitState();

				//to keep tack of state history (previous and current state)
				if (StateHistory.Num() < StateHistoryLength)
				{
					StateHistory.Push(CurrentState);
				}
				else
				{
					//StateHistory.RemoveAt(0);
					StateHistory.Push(CurrentState);
				}

				//set new state to current one
				CurrentState = NewState;
			}
		}

		//for saftey, check again if current state exists and then enter
		if (CurrentState)
		{
			CurrentState->OnEnterState(GetOwner());
			bCanTickState = true;
		}
	}
	else
	{
		if (bDebug)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, this->GetOwner()->GetName() + "'s state switch failed. " + "Invalid state!");
		}
	}


}


void UStateManagerComponent::InitStateManager()
{

	SwitchStateByKey(InitialState);
}

void UStateManagerComponent::InitializeStates()
{
	
	for (auto It = AvailableStates.CreateConstIterator(); It; ++It)				//go through available state list
	{
		UStateBase* State = NewObject<UStateBase>(this, It->Value);				//for each state found, create object and add to stateMap
		StateMap.Add(It->Key, State);
	}
}

