// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithPlayerState.h"

#include "Wraith/AbilitySystem/WraithAbilitySystemComponent.h"
#include "Wraith/AbilitySystem/AttributeSet/WraithAttributeSet.h"
#include "Wraith/AbilitySystem/AttributeSet/WraithCommonAttributeSet.h"

AWraithPlayerState::AWraithPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UWraithAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);
	AttributeSet = CreateDefaultSubobject<UWraithCommonAttributeSet>(TEXT("AttributeSet"));
}

void AWraithPlayerState::SetGenericTeamId(const FGenericTeamId& InTeamID)
{
	TeamID = InTeamID;
}

FGenericTeamId AWraithPlayerState::GetGenericTeamId() const
{
	return TeamID;
}

UAbilitySystemComponent* AWraithPlayerState::GetAbilitySystemComponent() const
{
	return GetWraithAbilitySystemComponent();
}

UAttributeSet* AWraithPlayerState::GetAttributeSet() const
{
	return GetWraithAttributeSet();
}
