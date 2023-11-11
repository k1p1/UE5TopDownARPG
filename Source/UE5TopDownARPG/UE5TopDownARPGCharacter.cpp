// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5TopDownARPGCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "UE5TopDownARPGGameMode.h"
#include "UE5TopDownARPG.h"

AUE5TopDownARPGCharacter::AUE5TopDownARPGCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	OnTakeAnyDamage.AddDynamic(this, &AUE5TopDownARPGCharacter::TakeAnyDamage);
}

void AUE5TopDownARPGCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

		FHitResult HitResult;
		FVector TraceStartLocation = GetActorLocation();
		FVector TraceEndLocation = GetActorLocation() + GetActorForwardVector() * 300.0f;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStartLocation, TraceEndLocation, ECollisionChannel::ECC_WorldDynamic, Params))
		{
			UE_LOG(LogUE5TopDownARPG, Log, TEXT("TraceHit %s %s"), *HitResult.GetActor()->GetName(), *HitResult.GetComponent()->GetName());
		}
}

void AUE5TopDownARPGCharacter::TakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigateBy, AActor* DamageCauser)
{
	Health -= Damage;
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("Health %f"), Health);
	if (Health <= 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(DeathHandle, this, &AUE5TopDownARPGCharacter::Death, DeathDelay);
	}
}

void AUE5TopDownARPGCharacter::Death()
{
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("Death"));
	AUE5TopDownARPGGameMode* GameMode = Cast<AUE5TopDownARPGGameMode>(GetWorld()->GetAuthGameMode());
	if (IsValid(GameMode))
	{
		GameMode->EndGame(false);
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector Location = GetActorLocation();
	FRotator Rotation = GetActorRotation();
	AActor* SpawnedActor = GetWorld()->SpawnActor(AfterDeathSpawnClass, &Location, &Rotation, SpawnParameters);
	if (IsValid(SpawnedActor))
	{

	}

	GetWorld()->GetTimerManager().ClearTimer(DeathHandle);
	Destroy();
}
