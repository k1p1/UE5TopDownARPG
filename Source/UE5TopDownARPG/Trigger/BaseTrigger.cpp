// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTrigger.h"
#include "Kismet/GameplayStatics.h"
#include "../UE5TopDownARPGCharacter.h"

// Sets default values
ABaseTrigger::ABaseTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollisionComponent"));
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SphereComponent->SetupAttachment(RootComponent);

	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ABaseTrigger::OnOverlapBegin);
	SphereComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &ABaseTrigger::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ABaseTrigger::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseTrigger::ActionStart(AActor* ActorInRange)
{

}

void ABaseTrigger::ActionEnd(AActor* ActorInRange)
{

}

void ABaseTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ActionStart(Other);
}

void ABaseTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ActionEnd(Other);
}

// Called every frame
void ABaseTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

