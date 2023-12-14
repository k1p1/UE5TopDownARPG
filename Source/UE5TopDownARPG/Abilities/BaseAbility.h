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
	virtual bool Activate(FVector Location);
	virtual bool IsSupportedForNetworking() const override { return true; }
	virtual bool CallRemoteFunction(UFunction* Function, void* Params, struct FOutParmRec* OutParms, FFrame* Stack) override;
	virtual int32 GetFunctionCallspace(UFunction* Fuction, FFrame* Stack) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	float Cooldown = 1.0f;

	bool bIsInCooldown = false;

	FTimerHandle CooldownTimerHandle;

private:
	void OnCooldownEnded();
};
