// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "TeleportAbility.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API UTeleportAbility : public UBaseAbility
{
	GENERATED_BODY()

public:
	virtual bool Activate(FVector Location) override;

private:
	UPROPERTY(EditDefaultsOnly)
	float MaxRange;

	UPROPERTY(EditDefaultsOnly)
	float MinRange;

	UPROPERTY(EditDefaultsOnly)
	bool CanTeleportOverObstacle;

	UPROPERTY(EditDefaultsOnly)
	bool DoesRetract;

	UPROPERTY(EditDefaultsOnly)
	float ZOffset = 100.0f;
};
