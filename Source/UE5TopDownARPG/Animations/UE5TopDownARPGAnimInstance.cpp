// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5TopDownARPGAnimInstance.h"

void UUE5TopDownARPGAnimInstance::SetIsAttacking(bool InIsAttacking)
{
  IsAttacking = InIsAttacking;
}

void UUE5TopDownARPGAnimInstance::AnimNotify_AttackFinished()
{
  IsAttacking = false;
}
