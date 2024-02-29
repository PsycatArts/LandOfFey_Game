// Fill out your copyright notice in the Description page of Project Settings.


#include "Elements/ElementDark.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

void UElementDark::OnEnterElement(AActor* ElementOwner)
{
	Super::OnEnterElement(ElementOwner);
}

void UElementDark::TickElement()
{
	Super::TickElement();

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("dark elem active"));
}

void UElementDark::OnExitElement()
{
	Super::OnExitElement();
}


