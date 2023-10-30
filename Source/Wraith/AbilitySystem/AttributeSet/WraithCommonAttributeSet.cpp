// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithCommonAttributeSet.h"

#include "GameplayEffectExtension.h"

void UWraithCommonAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UWraithCommonAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}
