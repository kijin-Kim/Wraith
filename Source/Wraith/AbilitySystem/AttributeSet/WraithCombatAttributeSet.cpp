// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithCombatAttributeSet.h"

void UWraithCombatAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if(Attribute == GetAttackComboCountAttribute())
	{
		NewValue = static_cast<int32>(NewValue) % 4;
	}
}

void UWraithCombatAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}
