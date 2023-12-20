// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5TopDownARPGAIController.h"
#include "UE5TopDownARPGCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

AUE5TopDownARPGAIController::AUE5TopDownARPGAIController()
{
  BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));
  BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
}

void AUE5TopDownARPGAIController::OnPossess(APawn* InPawn)
{
  Super::OnPossess(InPawn);

  AUE5TopDownARPGCharacter* PossessedCharacter = Cast<AUE5TopDownARPGCharacter>(InPawn);
  if (IsValid(PossessedCharacter))
  {
    UBehaviorTree* BehaviorTree = PossessedCharacter->GetBehaviorTree();
    if (IsValid(BehaviorTree))
    {
      BlackboardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
      BehaviorComp->StartTree(*BehaviorTree);
    }
  }
}

void AUE5TopDownARPGAIController::OnUnPossess()
{
  Super::OnUnPossess();

  BehaviorComp->StopTree();
}
