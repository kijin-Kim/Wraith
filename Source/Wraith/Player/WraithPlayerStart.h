// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "WraithPlayerStart.generated.h"

class UWraithCharacterDescription;
class UWraithInputConfig;
class UWraithPlayerData;

UCLASS()
class WRAITH_API AWraithPlayerStart : public APlayerStart
{
	GENERATED_BODY()

public:
	const UWraithInputConfig* GetPlayerInputConfig() const;
	const UWraithCharacterDescription* GetPlayerCharacterDescription() const;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<const UWraithPlayerData> PlayerData;
};
