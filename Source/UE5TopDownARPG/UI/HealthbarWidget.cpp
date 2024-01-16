// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthbarWidget.h"
#include "Components/ProgressBar.h"

void UHealthbarWidget::SetPercent(float InPercent)
{
  float Percent = FMath::Max(FMath::Min(InPercent, 1.0f), 0.f);
  HealthProgressBar->SetPercent(Percent);
}
