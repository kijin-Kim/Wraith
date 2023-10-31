// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithBlueprintFunctionLibrary.h"

#include "AbilitySystemGlobals.h"
#include "AbilitySystem/WraithAbilitySystemComponent.h"

UWraithAbilitySystemComponent* UWraithBlueprintFunctionLibrary::GetWraithAbilitySystemComponent(const UObject* WorldContextObject)
{
	return Cast<UWraithAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Cast<AActor>(WorldContextObject)));
}
