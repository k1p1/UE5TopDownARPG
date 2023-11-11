// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTrigger.h"
#include "WinTrigger.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API AWinTrigger : public ABaseTrigger
{
	GENERATED_BODY()

protected:
	virtual void ActionStart(AActor* ActorInRange) override;
	
};
