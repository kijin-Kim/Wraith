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
	virtual void InitGameState() override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

private:
	void LoadGameDescription(const UWraithGameDescription* WraithGameDescription) const;
	void InterceptDefaultPawnClass(const AController* InController);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta= (AllowPrivateAccess = "true"))
	TObjectPtr<UWraithGameDescription> DefaultGameDescription;
};
