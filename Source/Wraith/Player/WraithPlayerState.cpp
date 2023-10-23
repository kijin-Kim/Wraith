// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithPlayerState.h"

#include "Wraith/AbilitySystem/WraithAbilitySet.h"
#include "Wraith/AbilitySystem/WraithAbilitySystemComponent.h"
#include "Wraith/AbilitySystem/AttributeSet/WraithAttributeSet.h"
#include "Wraith/AbilitySystem/AttributeSet/WraithCommonAttributeSet.h"

AWraithPlayerState::AWraithPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UWraithAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);

	AttributeSet = CreateDefaultSubobject<UWraithCommonAttributeSet>(TEXT("AttributeSet"));
}

void AWraithPlayerState::SetWraithPlayerData(const UWraithPlayerData* InWraithPlayerData)
{
	WraithPlayerData = InWraithPlayerData;
	check(WraithPlayerData);
	AbilitySystemComponent->OriginateFromAbilitySet(WraithPlayerData->WraithAbilitySet);
}

UAbilitySystemComponent* AWraithPlayerState::GetAbilitySystemComponent() const
{
	return GetWraithAbilitySystemComponent();
}

UAttributeSet* AWraithPlayerState::GetAttributeSet() const
{
	return GetWraithAttributeSet();
}
