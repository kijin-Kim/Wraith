// Copyright Epic Games, Inc. All Rights Reserved.

#include "WraithGameMode.h"

#include "WraithGameState.h"
#include "Wraith/Wraith.h"
#include "Wraith/Player/WraithPlayerController.h"
#include "Wraith/Player/WraithPlayerStart.h"
#include "Wraith/Player/WraithPlayerState.h"
#include "Wraith/UI/WraithHUD.h"
#include "Wraith/Character/WraithCharacter.h"
#include "Wraith/Character/WraithExtensionComponent.h"

AWraithGameMode::AWraithGameMode()
{
	GameStateClass = AWraithGameState::StaticClass();
	HUDClass = AWraithHUD::StaticClass();
	PlayerControllerClass = AWraithPlayerController::StaticClass();
	PlayerStateClass = AWraithPlayerState::StaticClass();
	DefaultPawnClass = AWraithCharacter::StaticClass();
	bUseSeamlessTravel = true;
}

APawn* AWraithGameMode::SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform)
{
	APawn* ResultPawn = Super::SpawnDefaultPawnAtTransform_Implementation(NewPlayer, SpawnTransform);
	
	if (const AWraithPlayerStart* WraithPlayerStart = Cast<AWraithPlayerStart>(NewPlayer->StartSpot))
	{
		const AWraithCharacter* WraithCharacter = CastChecked<AWraithCharacter>(ResultPawn);
		UWraithExtensionComponent* ExtensionComponent = WraithCharacter->GetExtensionComponent();
		ExtensionComponent->CharacterDescription = WraithPlayerStart->GetPlayerCharacterDescription();
		AWraithPlayerController* WraithPlayerController = CastChecked<AWraithPlayerController>(NewPlayer);
		WraithPlayerController->InputConfig = WraithPlayerStart->GetPlayerInputConfig();
	}
	else
	{
		UE_LOG(LogWraith, Warning, TEXT("Default PlayerStart 대신 WraithPlayerStart를 사용하세요."));
	}

	return ResultPawn;
}
