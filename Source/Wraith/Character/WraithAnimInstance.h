// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Animation/AnimInstance.h"
#include "WraithAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class WRAITH_API UWraithAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

private:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTagBlueprintPropertyMap GameplayTagPropertyMap;
};
