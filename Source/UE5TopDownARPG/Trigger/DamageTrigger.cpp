// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTrigger.h"
#include "Engine/DamageEvents.h"

void ADamageTrigger::ActionStart(AActor* ActorInRange)
{
  Target = ActorInRange;

  GetWorld()->GetTimerManager().SetTimer(CustomDamageTickTimerHandle, this, &ADamageTrigger::DamageTick, DamageTickRate, true);
}

void ADamageTrigger::ActionEnd(AActor* ActorInRange)
{
  Target = nullptr;
  GetWorld()->GetTimerManager().ClearTimer(CustomDamageTickTimerHandle);
}

void ADamageTrigger::DamageTick()
{
  if (IsValid(Target))
  {
    Target->TakeDamage(Damage, FDamageEvent(UDamageType::StaticClass()), nullptr, this);
  }
}
