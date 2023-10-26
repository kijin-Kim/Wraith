// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "WraithInputConfig.generated.h"


class UInputMappingContext;
class UEnhancedInputUserSettings;
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


USTRUCT(BlueprintType)
struct FWraithInputMappingContext
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> InputMappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Priority = 0;
};

/**
 * 
 */
UCLASS(BlueprintType)
class WRAITH_API UWraithInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag) const;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (TitleProperty = "InputAction"))
	TArray<FWraithInputAction> NativeInputActions;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (TitleProperty = "InputAction"))
	TArray<FWraithInputAction> AbilityInputActions;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (TitleProperty = "InputMappingContext"))
	TArray<FWraithInputMappingContext> InputMappingContexts;
	
};
