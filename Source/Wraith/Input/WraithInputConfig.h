// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "WraithInputConfig.generated.h"


class UPlayerMappableInputConfig;
class UInputAction;

USTRUCT(BlueprintType)
struct FWraithInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> InputAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag InputTag;
};

/**
 * 
 */
UCLASS(BlueprintType)
class WRAITH_API UWraithInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag);
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (TitleProperty = "InputAction"))
	TArray<FWraithInputAction> NativeInputActions;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (TitleProperty = "InputAction"))
	TArray<FWraithInputAction> AbilityInputActions;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (TitleProperty = "Player Mappable Input Config"))
	TArray<TObjectPtr<UPlayerMappableInputConfig>> PlayerMappableInputConfigs;
	
};
