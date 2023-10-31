// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "WraithCheatManager.generated.h"

/**
 * 
 */
UCLASS()
class WRAITH_API UWraithCheatManager : public UCheatManager
{
	GENERATED_BODY()
public:
	UFUNCTION(Exec)
	void CycleAbilitySystemDebug();
};
