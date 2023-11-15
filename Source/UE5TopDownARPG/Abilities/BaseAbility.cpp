// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAbility.h"
#include "Engine/World.h"
#include "../UE5TopDownARPG.h"

bool UBaseAbility::Activate(FVector Location)
{
  UE_LOG(LogUE5TopDownARPG, Log, TEXT("UBaseAbility::Activate"));

  if (bIsInCooldown)
  {
    return false;
  }

  bIsInCooldown = true;

  FTimerManager& TimerManager = GetWorld()->GetTimerManager();
  TimerManager.SetTimer(CooldownTimerHandle, this, &UBaseAbility::OnCooldownEnded, Cooldown);

  return true;
}

void UBaseAbility::OnCooldownEnded()
{
  bIsInCooldown = false;

  FTimerManager& TimerManager = GetWorld()->GetTimerManager();
  TimerManager.ClearTimer(CooldownTimerHandle);
}