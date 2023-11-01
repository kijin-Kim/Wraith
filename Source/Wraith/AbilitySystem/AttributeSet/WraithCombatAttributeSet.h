// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "WraithAttributeSet.h"
#include "WraithCombatAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class WRAITH_API UWraithCombatAttributeSet : public UWraithAttributeSet
{
	GENERATED_BODY()
	
public:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

public:
	UPROPERTY(BlueprintReadOnly, Category="Combat")
	FGameplayAttributeData AttackComboCount;
	ATTRIBUTE_ACCESSORS(UWraithCombatAttributeSet, AttackComboCount);
	UPROPERTY(BlueprintReadOnly, Category="Combat")
	FGameplayAttributeData MaxAttackComboCount;
	ATTRIBUTE_ACCESSORS(UWraithCombatAttributeSet, MaxAttackComboCount);
};
