// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithAnimInstance.h"

#include "AbilitySystemGlobals.h"

void UWraithAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (AActor* OwningActor = GetOwningActor())
	{
		if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwningActor))
		{
			GameplayTagPropertyMap.Initialize(this, ASC);
		}
	}
}
