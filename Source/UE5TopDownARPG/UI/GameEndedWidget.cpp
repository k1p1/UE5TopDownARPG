// Fill out your copyright notice in the Description page of Project Settings.


#include "GameEndedWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UGameEndedWidget::NativeConstruct()
{
  Super::NativeConstruct();

  FScriptDelegate OnPlayButtonClickedDelegate;
  OnPlayButtonClickedDelegate.BindUFunction(this, FName("OnPlayButtonClickedHandler"));
  PlayButton->OnClicked.AddUnique(OnPlayButtonClickedDelegate);

  FScriptDelegate OnQuitButtonClickedDelegate;
  OnQuitButtonClickedDelegate.BindUFunction(this, FName("OnQuitButtonClickedHandler"));
  QuitButton->OnClicked.AddUnique(OnQuitButtonClickedDelegate);
}

void UGameEndedWidget::OnPlayButtonClickedHandler()
{
  UGameplayStatics::OpenLevel(this, FName(*FirstWorld.GetAssetName()), true);
}

void UGameEndedWidget::OnQuitButtonClickedHandler()
{
  UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
}
