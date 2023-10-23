// Copyright Epic Games, Inc. All Rights Reserved.

#include "WraithGameMode.h"

#include "WraithGameDescription.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Wraith/Character/WraithCharacter.h"
#include "Wraith/Player/WraithPlayerData.h"
#include "Wraith/Player/WraithPlayerState.h"

AWraithGameMode::AWraithGameMode()
{
}

void AWraithGameMode::InitGameState()
{
	Super::InitGameState();

	if (OptionsString.IsEmpty())
	{
		LoadGameDescription(DefaultGameDescription);
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
	OptionString += FString::Printf(TEXT("?WraithPlayerDataID=%s"), *WraithGameDescription->WraithPlayerDataID.PrimaryAssetName.ToString());
	GetWorld()->ServerTravel(OptionString);
}

void AWraithGameMode::InterceptDefaultPawnClass(const AController* InController)
{
	if (UGameplayStatics::HasOption(OptionsString, TEXT("WraithPlayerDataID")))
	{
		const FString Parsed = UGameplayStatics::ParseOption(OptionsString, TEXT("WraithPlayerDataID"));
		const FPrimaryAssetId WraithPlayerDataID = FPrimaryAssetId(UWraithPlayerData::StaticClass()->GetFName(), *Parsed);
		const FSoftObjectPath AssetPath = UAssetManager::Get().GetPrimaryAssetPath(WraithPlayerDataID);
		const TSubclassOf<UWraithPlayerData> WraithPlayerDataClass = Cast<UClass>(AssetPath.TryLoad());
		check(WraithPlayerDataClass);

		const UWraithPlayerData* WraithPlayerData = GetDefault<UWraithPlayerData>(WraithPlayerDataClass);
		if (WraithPlayerData && WraithPlayerData->WraithCharacterClass)
		{
			AWraithPlayerState* WraithPlayerState = InController->GetPlayerState<AWraithPlayerState>();
			check(WraithPlayerState);
			WraithPlayerState->SetWraithPlayerData(WraithPlayerData);
			DefaultPawnClass = Cast<APawn>(WraithPlayerData->WraithCharacterClass.GetDefaultObject())->GetClass();
		}
	}
}
