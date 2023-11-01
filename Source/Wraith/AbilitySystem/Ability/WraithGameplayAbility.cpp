// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithGameplayAbility.h"

#include "Wraith/Character/WraithCharacter.h"

FName UWraithGameplayAbility::GetAvatarActorDataTableID() const
{
	const AWraithCharacter* WraithCharacter = GetAvatarActorAsWraithCharacter();
	if (!WraithCharacter)
	{
		return {};
	}

	if (const UWraithCharacterDescription* WraithCharacterDescription = WraithCharacter->GetCharacterDescription())
	{
		return WraithCharacterDescription->DataTableID;
	}

	return {};
}

AWraithCharacter* UWraithGameplayAbility::GetAvatarActorAsWraithCharacter() const
{
	return Cast<AWraithCharacter>(GetAvatarActorFromActorInfo());
}
