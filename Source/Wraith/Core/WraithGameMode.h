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

	UFUNCTION(BlueprintCallable)
	void LoadGameDescription(const UWraithGameDescription* WraithGameDescription) const;
	
private:
	void InterceptDefaultPawnClass(const AController* InController);

	UPROPERTY()
	TObjectPtr<UWraithGameDescription> CurrentGameDescription;
	
};
