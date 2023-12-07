// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "UE5TopDownARPGAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API UUE5TopDownARPGAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	void SetIsAttacking();

protected:
	UPROPERTY(EditDefaultsOnly)
	UAnimSequenceBase* AttackAnimation;
	
};
