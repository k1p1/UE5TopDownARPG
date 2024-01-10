// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameEndedWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API UGameEndedWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
		void OnPlayButtonClickedHandler();

	UFUNCTION()
		void OnQuitButtonClickedHandler();

	UPROPERTY(EditAnywhere)
		TSoftObjectPtr<UWorld> FirstWorld;

	UPROPERTY(meta = (BindWidget))
		class UButton* PlayButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* QuitButton;

};
