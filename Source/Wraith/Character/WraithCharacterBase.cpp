// Copyright Epic Games, Inc. All Rights Reserved.

#include "WraithCharacterBase.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "Wraith/AbilitySystem/WraithAttributeSet.h"
#include "Wraith/Player/WraithPlayerState.h"

AWraithCharacterBase::AWraithCharacterBase()
{

}

void AWraithCharacterBase::InitializeAbilitySystem(AActor* OwnerActor, AActor* AvatarActor) const
{
	GetAbilitySystemComponent()->InitAbilityActorInfo(OwnerActor, AvatarActor);
}

UAbilitySystemComponent* AWraithCharacterBase::GetAbilitySystemComponent() const
{
	return GetWraithAbilitySystemComponent();
}

UAttributeSet* AWraithCharacterBase::GetAttributeSet() const
{
	return GetWraithAttributeSet();
}


