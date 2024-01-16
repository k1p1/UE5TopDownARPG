// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5TopDownARPGHUD.h"
#include "UI/EndGameWidget.h"
#include "Kismet/GameplayStatics.h"

void AUE5TopDownARPGHUD::BeginPlay()
{
  Super::BeginPlay();

  APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
  if (IsValid(PlayerController))
  {
    EndGameWidget = CreateWidget<UEndGameWidget>(PlayerController, EndGameWidgetClass);
    if (IsValid(EndGameWidget))
    {
      EndGameWidget->AddToViewport();
      EndGameWidget->SetVisibility(ESlateVisibility::Collapsed);
    }
  }
}

void AUE5TopDownARPGHUD::ShowEndGameScreen()
{
  if (IsValid(EndGameWidget))
  {
    EndGameWidget->SetVisibility(ESlateVisibility::Visible);
  }
}