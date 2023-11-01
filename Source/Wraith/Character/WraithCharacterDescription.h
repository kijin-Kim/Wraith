// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "WraithCharacterDescription.generated.h"

class UAttributeSet;
class UWraithAttributeSet;
class UGameplayAbility;
class UGameplayEffect;


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
	float Level = 1.0f;
};

/**
 * 
 */
UCLASS(BlueprintType)
class WRAITH_API UWraithCharacterDescription : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	FName DataTableID;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character") 
	TObjectPtr<USkeletalMesh> SkeletalMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	TArray<TSubclassOf<UActorComponent>> Components;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	TArray<FWraithGameplayAbilityConfig> GrantedAbilities;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	TArray<FWraithGameplayEffectConfig> GrantedGameplayEffects;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	TArray<TSubclassOf<UAttributeSet>> GrantedAttributeSets;
	
};
