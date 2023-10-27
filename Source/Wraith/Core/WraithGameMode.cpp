// Copyright Epic Games, Inc. All Rights Reserved.

#include "WraithGameMode.h"

#include "WraithGameDescription.h"
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

void AWraithGameMode::InitGameState()
{
	Super::InitGameState();
	if (OptionsString.IsEmpty())
	{
		const AWraithWorldSettings* WraithWorldSettings = Cast<AWraithWorldSettings>(GetWorldSettings());
		LoadGameDescription(WraithWorldSettings->DefaultGameDescription);
	}
}

UClass* AWraithGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	InterceptDefaultPawnClass(InController);
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AWraithGameMode::LoadGameDescription(const UWraithGameDescription* WraithGameDescription) const
{
	if (!WraithGameDescription)
	{
		return;
	}
	
	FAssetData MapAssetData;
	UAssetManager::Get().GetPrimaryAssetData(WraithGameDescription->MapID, MapAssetData);
	FString OptionString = MapAssetData.PackageName.ToString();
	OptionString += FString::Printf(TEXT("?WraithPlayerDataID=%s"), *WraithGameDescription->PlayerDataID.PrimaryAssetName.ToString());
	GetWorld()->ServerTravel(OptionString);
}



void AWraithGameMode::InterceptDefaultPawnClass(const AController* InController)
{
	if (UGameplayStatics::HasOption(OptionsString, TEXT("WraithPlayerDataID")))
	{
		// Sync Load
		// TODO: 로딩화면에서 Unload
		const FString Parsed = UGameplayStatics::ParseOption(OptionsString, TEXT("WraithPlayerDataID"));
		const FPrimaryAssetId WraithPlayerDataID = FPrimaryAssetId(UWraithPlayerData::StaticClass()->GetFName(), *Parsed);
		const FSoftObjectPath AssetPath = UAssetManager::Get().GetPrimaryAssetPath(WraithPlayerDataID);
		const UWraithPlayerData* WraithPlayerData = Cast<UWraithPlayerData>(AssetPath.TryLoad());
		
		if (WraithPlayerData && WraithPlayerData->PawnClass)
		{
			AWraithPlayerState* WraithPlayerState = InController->GetPlayerState<AWraithPlayerState>();
			check(WraithPlayerState);
			WraithPlayerState->SetPlayerData(WraithPlayerData);
			DefaultPawnClass = Cast<APawn>(WraithPlayerData->PawnClass.GetDefaultObject())->GetClass();
		}
	}
}
