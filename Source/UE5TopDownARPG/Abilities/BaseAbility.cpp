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

bool UBaseAbility::CallRemoteFunction(UFunction* Function, void* Params, FOutParmRec* OutParms, FFrame* Stack)
{
    AActor* SkillOuter = Cast<AActor>(GetOuter());
    if (IsValid(SkillOuter) == false)
    {
      return false;
    }

    UNetDriver* NetDriver = SkillOuter->GetNetDriver();
    if (IsValid(NetDriver) == false)
    {
      return false;
    }

    NetDriver->ProcessRemoteFunction(SkillOuter, Function, Params, OutParms, Stack, this);

    return true;
}

int32 UBaseAbility::GetFunctionCallspace(UFunction* Function, FFrame* Stack)
{
  AActor* SkillOuter = Cast<AActor>(GetOuter());
  return (SkillOuter ? SkillOuter->GetFunctionCallspace(Function, Stack) : FunctionCallspace::Local);
}

void UBaseAbility::OnCooldownEnded()
{
  bIsInCooldown = false;

  FTimerManager& TimerManager = GetWorld()->GetTimerManager();
  TimerManager.ClearTimer(CooldownTimerHandle);
}