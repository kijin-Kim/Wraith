// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithCharacterMovementComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Wraith/AbilitySystem/AttributeSet/WraithCommonAttributeSet.h"

void UWraithCharacterMovementComponent::InitializeWithAbilitySystemComponent()
{
	UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner(), false);
	check(AbilitySystemComponent);
	const UWraithCommonAttributeSet* CommonAttributeSet = AbilitySystemComponent->GetSet<UWraithCommonAttributeSet>();
	if (!CommonAttributeSet)
	{
		return;
	}

	BaseMaxWalkSpeed = MaxWalkSpeed;
	BaseMaxCustomMovementSpeed = MaxCustomMovementSpeed;
	BaseMaxFlySpeed = MaxFlySpeed;
	BaseMaxSwimSpeed = MaxSwimSpeed;
	BaseMaxWalkSpeedCrouched = MaxWalkSpeedCrouched;

	auto& OnSpeedPercentChangedDelegate = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CommonAttributeSet->GetSpeedPercentAttribute());
	OnSpeedPercentChangedDelegate.AddUObject(this, &ThisClass::OnSpeedPercentChanged);
}

void UWraithCharacterMovementComponent::OnSpeedPercentChanged(const FOnAttributeChangeData& OnAttributeChangeData)
{
	const float NewPercent = OnAttributeChangeData.NewValue;
	MaxWalkSpeed = BaseMaxWalkSpeed * NewPercent;
	MaxCustomMovementSpeed = BaseMaxCustomMovementSpeed * NewPercent;
	MaxFlySpeed = BaseMaxFlySpeed * NewPercent;
	MaxSwimSpeed = BaseMaxSwimSpeed * NewPercent;
	MaxWalkSpeedCrouched = BaseMaxWalkSpeedCrouched * NewPercent;
}
