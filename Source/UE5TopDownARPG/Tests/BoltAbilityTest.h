#pragma once

#include "Tests/AutomationCommon.h"

DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FLatent_ActivateAbility,
	class AUE5TopDownARPGCharacter*, ActiveCharacter,
	class AUE5TopDownARPGCharacter*, TargetCharacter);

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FLatent_CheckBoltAbilityTargetHealth,
	class AUE5TopDownARPGCharacter*, Target,
	float, StartingHealth,
	float, ExpectedHealth);