// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5TopDownARPGAIController.h"
#include "../UE5TopDownARPGCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"

AUE5TopDownARPGAIController::AUE5TopDownARPGAIController()
{
  BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
  BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
}

void AUE5TopDownARPGAIController::OnPossess(APawn* InPawn)
{
  Super::OnPossess(InPawn);

  AUE5TopDownARPGCharacter* PossesedCharacter = Cast<AUE5TopDownARPGCharacter>(InPawn);
  if (IsValid(PossesedCharacter))
  {
    UBehaviorTree* Tree = PossesedCharacter->GetBehaviorTree();
    if (IsValid(Tree))
    {
      BlackboardComponent->InitializeBlackboard(*Tree->GetBlackboardAsset());
      BehaviorTreeComponent->StartTree(*Tree);
    }
  }
}

void AUE5TopDownARPGAIController::OnUnPossess()
{
  Super::OnUnPossess();

  BehaviorTreeComponent->StopTree();
}