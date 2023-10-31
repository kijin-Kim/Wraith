// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithCheatManager.h"

#include "GameFramework/HUD.h"

void UWraithCheatManager::CycleAbilitySystemDebug()
{
	// This code is from Lyra Starter Project 
	APlayerController* PC = Cast<APlayerController>(GetOuterAPlayerController());
	if (PC && PC->MyHUD)
	{
		if (!PC->MyHUD->bShowDebugInfo || !PC->MyHUD->DebugDisplay.Contains(TEXT("AbilitySystem")))
		{
			PC->MyHUD->ShowDebug(TEXT("AbilitySystem"));
		}

		PC->ConsoleCommand(TEXT("AbilitySystem.Debug.NextCategory"));
	}
}
