// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithPlayerState.h"

#include "Wraith/AbilitySystem/WraithAbilitySystemComponent.h"
#include "Wraith/AbilitySystem/WraithAttributeSet.h"

AWraithPlayerState::AWraithPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UWraithAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UWraithAttributeSet>(TEXT("AttributeSet"));

	NetUpdateFrequency = 30.0f;
}

UAbilitySystemComponent* AWraithPlayerState::GetAbilitySystemComponent() const
{
	return GetWraithAbilitySystemComponent();
}

UAttributeSet* AWraithPlayerState::GetAttributeSet() const
{
	return GetWraithAttributeSet();
}
