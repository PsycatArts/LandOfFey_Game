// Fill out your copyright notice in the Description page of Project Settings.


#include "Elements/ElementLight.h"

void UElementLight::OnEnterElement(AActor* ElementOwner)
{
	Super::OnEnterElement(ElementOwner);


}

void UElementLight::TickElement()
{
	Super::TickElement();

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("light elem active"));
}

void UElementLight::OnExitElement()
{
	Super::OnExitElement();

}

//void UElementLight::Enemy_Ability(AActor* TargetActor)
//{
//	Super::Enemy_Ability(TargetActor);
//
//
//
//}
//
