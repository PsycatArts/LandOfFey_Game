// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PlayerStateBase.h"
#include "PlayerStateAttack.generated.h"

/**
 * 
 */
UCLASS()
class THELANDOFFEY_API UPlayerStateAttack : public UPlayerStateBase
{
	GENERATED_BODY()

protected:

	void Attacking();
	virtual void TickState() override;
	virtual void OnEnterState(AActor* StateOwner) override;
	virtual void OnExitState() override;

	void ResetMainAttack();




	//RESET COMBO
	int ComboAttack_Num;
	FTimerHandle ComboResetTimer;	//timer to count down
	//after X seconds, combo will be reset back to first attack
	float ComboResetTime = 1.2f;;


	bool bAllowNextAttack = true;

	//ATTACK ANIMATION MONTAGES
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")		//var to assign the montage
		UAnimMontage* MainAttack_1_Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")		//var to assign the montage
		UAnimMontage* MainAttack_2_Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")		//var to assign the montage
		UAnimMontage* MainAttack_3_Montage;
	/*void MainAttack_End();*/
	
};
