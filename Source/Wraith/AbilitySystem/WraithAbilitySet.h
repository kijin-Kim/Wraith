// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "WraithAbilitySet.generated.h"

class UGameplayEffect;
class UGameplayAbility;


USTRUCT(BlueprintType)
struct FWraithGameplayAbilityConfig
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayAbility")
	TSubclassOf<UGameplayAbility> Ability;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayAbility")
	int32 Level = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayAbility")
	FGameplayTag InputTag;
};

USTRUCT(BlueprintType)
struct FWraithGameplayEffectConfig
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayEffect")
	TSubclassOf<UGameplayEffect> Effect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayEffect")
	float Level;
};


/**
 * 
 */
UCLASS(BlueprintType)
class WRAITH_API UWraithAbilitySet : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilitySet")
	TArray<FWraithGameplayAbilityConfig> GrantedAbilities;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilitySet")
	TArray<FWraithGameplayEffectConfig> GrantedGameplayEffects;
};
