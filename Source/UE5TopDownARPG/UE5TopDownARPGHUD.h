// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UE5TopDownARPGHUD.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API AUE5TopDownARPGHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	void ShowEndGameScreen();

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> EndGameWidgetClass;
	UPROPERTY()
	class UEndGameWidget* EndGameWidget;
	
};
