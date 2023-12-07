// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5TopDownARPGAnimInstance.h"

void UUE5TopDownARPGAnimInstance::SetIsAttacking()
{
  PlaySlotAnimationAsDynamicMontage(AttackAnimation, FName(TEXT("UpperBody")));
}
