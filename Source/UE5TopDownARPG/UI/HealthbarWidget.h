// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthbarWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API UHealthbarWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthProgressBar;

public:
	void SetPercent(float InPercent);
	
};
