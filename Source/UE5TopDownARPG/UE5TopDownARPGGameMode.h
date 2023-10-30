// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UE5TopDownARPGGameMode.generated.h"

UCLASS(minimalapi)
class AUE5TopDownARPGGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUE5TopDownARPGGameMode();

	void EndGame(bool IsWin);
};



