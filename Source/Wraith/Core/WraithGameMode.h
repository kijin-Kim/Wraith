// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WraithGameMode.generated.h"

class UWraithGameDescription;

UCLASS(minimalapi)
class AWraithGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AWraithGameMode();
	virtual APawn* SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform) override;

};
