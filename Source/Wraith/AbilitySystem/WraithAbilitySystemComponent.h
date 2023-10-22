// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "WraithAbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WRAITH_API UWraithAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UWraithAbilitySystemComponent();
};
