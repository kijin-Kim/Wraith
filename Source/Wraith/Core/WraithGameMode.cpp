// Copyright Epic Games, Inc. All Rights Reserved.

#include "WraithGameMode.h"

#include "WraithGameState.h"
#include "WraithWorldSettings.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Wraith/Pawn/WraithPawn.h"
#include "Wraith/Player/WraithPlayerController.h"
#include "Wraith/Player/WraithPlayerData.h"
#include "Wraith/Player/WraithPlayerState.h"
#include "Wraith/UI/WraithHUD.h"

AWraithGameMode::AWraithGameMode()
{
	GameStateClass = AWraithGameState::StaticClass();
	HUDClass = AWraithHUD::StaticClass();
	PlayerControllerClass = AWraithPlayerController::StaticClass();
	PlayerStateClass = AWraithPlayerState::StaticClass();
	DefaultPawnClass = AWraithPawn::StaticClass();
	bUseSeamlessTravel = true;
}