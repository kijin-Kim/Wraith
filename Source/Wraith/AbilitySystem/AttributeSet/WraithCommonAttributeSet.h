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
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

public:
	// These Attribute Formula are Inspired by Genshin Impact
	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes")
	FGameplayAttributeData BaseAttack;
	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes")
	FGameplayAttributeData WeaponAttack;
	ATTRIBUTE_ACCESSORS(UWraithCommonAttributeSet, WeaponAttack);
	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes")
	FGameplayAttributeData AttackPercent;
	ATTRIBUTE_ACCESSORS(UWraithCommonAttributeSet, AttackPercent);
	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes")
	FGameplayAttributeData FlatAttack;
	ATTRIBUTE_ACCESSORS(UWraithCommonAttributeSet, FlatAttack);

	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes")
	FGameplayAttributeData BaseDefense;
	ATTRIBUTE_ACCESSORS(UWraithCommonAttributeSet, BaseDefense);
	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes")
	FGameplayAttributeData DefensePercent;
	ATTRIBUTE_ACCESSORS(UWraithCommonAttributeSet, DefensePercent);
	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes")
	FGameplayAttributeData FlatDefense;
	ATTRIBUTE_ACCESSORS(UWraithCommonAttributeSet, FlatDefense);
	
	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes")
	FGameplayAttributeData BaseHealth;
	ATTRIBUTE_ACCESSORS(UWraithCommonAttributeSet, BaseHealth);
	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes")
	FGameplayAttributeData HealthPercent;
	ATTRIBUTE_ACCESSORS(UWraithCommonAttributeSet, HealthPercent);
	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes")
	FGameplayAttributeData FlatHealth;
	ATTRIBUTE_ACCESSORS(UWraithCommonAttributeSet, FlatHealth);
	
	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes")
	FGameplayAttributeData BaseSpeed;

	
	// Attack = ( BaseAttack + WeaponAttack ) x ( 1 + AttackPercent ) + FlatAttack 
	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes")
	FGameplayAttributeData Attack;
	ATTRIBUTE_ACCESSORS(UWraithCommonAttributeSet, Attack);

	// Defense = BaseDefense x ( 1 + DefensePercent ) + FlatDefense
	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes")
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(UWraithCommonAttributeSet, Defense);

	// MaxHealth = BaseHealth x ( 1 + HealthPercent ) + FlatHealth
	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UWraithCommonAttributeSet, Health);
	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UWraithCommonAttributeSet, MaxHealth);
};
