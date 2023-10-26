// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithPlayerController.h"

#include "AbilitySystemGlobals.h"
#include "Wraith/AbilitySystem/WraithAbilitySystemComponent.h"
#include "Wraith/Character/WraithCharacter.h"

void AWraithPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	Super::PostProcessInput(DeltaTime, bGamePaused);
	if (UWraithAbilitySystemComponent* WraithAbilitySystemComponent = Cast<UWraithAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetPawn())))
	{
		WraithAbilitySystemComponent->HandleAbilityInputs();
	}
}
