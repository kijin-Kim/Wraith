// Copyright Epic Games, Inc. All Rights Reserved.

#include "WraithGameMode.h"
#include "WraithCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWraithGameMode::AWraithGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
