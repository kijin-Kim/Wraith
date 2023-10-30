// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "WraithCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class WRAITH_API UWraithCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	void InitializeWithAbilitySystemComponent();

private:
	void OnSpeedPercentChanged(const FOnAttributeChangeData& OnAttributeChangeData);


private:
	float BaseMaxWalkSpeed;
	float BaseMaxCustomMovementSpeed;
	float BaseMaxFlySpeed;
	float BaseMaxSwimSpeed;
	float BaseMaxWalkSpeedCrouched;
};
