// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WraithAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "WraithCommonAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class WRAITH_API UWraithCommonAttributeSet : public UWraithAttributeSet
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UWraithCommonAttributeSet, Strength);
	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes")
    FGameplayAttributeData Vital;
	ATTRIBUTE_ACCESSORS(UWraithCommonAttributeSet, Vital);
	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes")
	FGameplayAttributeData Agility;
	ATTRIBUTE_ACCESSORS(UWraithCommonAttributeSet, Agility);
	
	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UWraithCommonAttributeSet, Health);
	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UWraithCommonAttributeSet, MaxHealth);
	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes")
	FGameplayAttributeData WalkSpeed;
	ATTRIBUTE_ACCESSORS(UWraithCommonAttributeSet, WalkSpeed);
};
