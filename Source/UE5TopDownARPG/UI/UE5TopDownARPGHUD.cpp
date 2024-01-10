// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5TopDownARPGHUD.h"
#include "GameEndedWidget.h"
#include "Kismet/GameplayStatics.h"

void AUE5TopDownARPGHUD::BeginPlay()
{
  Super::BeginPlay();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (GameEndedWidgetClass != nullptr)
	{
		GameEndedWidget = CreateWidget<UGameEndedWidget>(PlayerController, GameEndedWidgetClass);
		if (IsValid(GameEndedWidget))
		{
			GameEndedWidget->AddToViewport();
			GameEndedWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void AUE5TopDownARPGHUD::ShowEndGameScreen()
{
	GameEndedWidget->SetVisibility(ESlateVisibility::Visible);
}