// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithCombatAttributeSet.h"

void UWraithCombatAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetAttackComboCountAttribute())
	{
		const int32 MaxComboCount = static_cast<int32>(GetMaxAttackComboCount());
		if (MaxComboCount > 0)
		{
			NewValue = static_cast<int32>(NewValue) % MaxComboCount;
		}
	}
}

void UWraithCombatAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}
