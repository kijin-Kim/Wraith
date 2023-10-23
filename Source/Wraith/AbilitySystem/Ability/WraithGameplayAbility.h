// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "WraithGameplayAbility.generated.h"


UENUM(BlueprintType)
enum class EWraithAbilityInputEventPolicy
{
	Pressed,
	Held,
	Spawned,
	Max UMETA(hidden)
};


/**
 * 
 */
UCLASS()
class WRAITH_API UWraithGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wraith|Input")
	EWraithAbilityInputEventPolicy InputEventPolicy = EWraithAbilityInputEventPolicy::Pressed;
	
};
