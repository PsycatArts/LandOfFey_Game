// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy/FeyStateBase.h"
#include "Kismet/GameplayStatics.h"


void UFeyStateBase::OnEnterState(AActor* OwnerRef)
{
	Super::OnEnterState(OwnerRef);

	if (!Fey)
	{
		Fey = Cast<AFeyAI>(OwnerRef);
	}

}

void UFeyStateBase::OnExitState()
{
	Super::OnExitState();

}

