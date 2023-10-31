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
	UWraithCharacterMovementComponent();
	void InitializeWithAbilitySystemComponent();

private:
	void OnSpeedPercentChanged(const FOnAttributeChangeData& OnAttributeChangeData);


private:
	float BaseMaxWalkSpeed = 0.0f;
	float BaseMaxCustomMovementSpeed = 0.0f;
	float BaseMaxFlySpeed = 0.0f;
	float BaseMaxSwimSpeed = 0.0f;
	float BaseMaxWalkSpeedCrouched = 0.0f;
};
