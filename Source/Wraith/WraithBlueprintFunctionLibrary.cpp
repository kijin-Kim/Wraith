// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithBlueprintFunctionLibrary.h"

#include "AbilitySystemGlobals.h"
#include "AbilitySystem/WraithAbilitySystemComponent.h"
#include "Character/WraithCharacter.h"
#include "Player/WraithCameraManagerComponent.h"

UWraithAbilitySystemComponent* UWraithBlueprintFunctionLibrary::GetWraithAbilitySystemComponent(const UObject* WorldContextObject)
{
	return Cast<UWraithAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Cast<AActor>(WorldContextObject)));
}

void UWraithBlueprintFunctionLibrary::SetTargetActorCameraData(AWraithCharacter* WraithCharacter, const UWraithCameraData* CameraData)
{
	if (!WraithCharacter || !CameraData)
	{
		return;
	}
	
	if (UWraithCameraManagerComponent* CameraManagerComponent = Cast<UWraithCameraManagerComponent>(
		WraithCharacter->GetComponentByClass(UWraithCameraManagerComponent::StaticClass())))
	{
		CameraManagerComponent->SetCameraData(CameraData);
	}
}
