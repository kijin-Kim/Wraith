// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WraithPlayerData.generated.h"


class UWraithAbilitySet;
class AWraithCharacter;
class UWraithInputConfig;
/**
 * 
 */
UCLASS(BlueprintType)
class WRAITH_API UWraithPlayerData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player")
	TObjectPtr<UWraithInputConfig> InputConfig;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player")
	TObjectPtr<UWraithAbilitySet> AbilitySet;
};
