// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlackSurvivalGameMode.h"
#include "BlackSurvivalCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABlackSurvivalGameMode::ABlackSurvivalGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
        DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
