// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseAbility.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UE5TOPDOWNARPG_API UBaseAbility : public UObject
{
	GENERATED_BODY()
	
public:
  virtual void BeginDestroy();

  UFUNCTION()
  virtual bool Activate(FVector AimLocation);

  UFUNCTION()
  bool IsOffCooldown() const { return bIsOffCooldown; }
  
  UPROPERTY(EditDefaultsOnly)
  float CooldownTime = 1.f;

private:
  bool bIsOffCooldown = true;
  FTimerManager* TimerManager = nullptr;
  FTimerHandle CooldownTimerHandle;
  void OnCooldownTimerEnded();
};
