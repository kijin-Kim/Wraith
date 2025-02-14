// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithCharacterMovementComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Wraith/Wraith.h"
#include "Wraith/AbilitySystem/AttributeSet/WraithCommonAttributeSet.h"

UWraithCharacterMovementComponent::UWraithCharacterMovementComponent()
{
	bUseAccelerationForPaths = true;
}

void UWraithCharacterMovementComponent::InitializeWithAbilitySystemComponent()
{
	UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner(), false);
	check(ASC);
	const UWraithCommonAttributeSet* CommonAttributeSet = ASC->GetSet<UWraithCommonAttributeSet>();
	if (!CommonAttributeSet)
	{
		return;
	}

	BaseMaxWalkSpeed = MaxWalkSpeed;
	BaseMaxCustomMovementSpeed = MaxCustomMovementSpeed;
	BaseMaxFlySpeed = MaxFlySpeed;
	BaseMaxSwimSpeed = MaxSwimSpeed;
	BaseMaxWalkSpeedCrouched = MaxWalkSpeedCrouched;

	auto& OnSpeedPercentChangedDelegate = ASC->GetGameplayAttributeValueChangeDelegate(CommonAttributeSet->GetSpeedPercentAttribute());
	OnSpeedPercentChangedDelegate.AddUObject(this, &ThisClass::OnSpeedPercentChanged);
}

void UWraithCharacterMovementComponent::OnSpeedPercentChanged(const FOnAttributeChangeData& OnAttributeChangeData)
{
	const float NewPercent = OnAttributeChangeData.NewValue;
	UE_LOG(LogWraith, Warning, TEXT("%f"), NewPercent);
	MaxWalkSpeed = BaseMaxWalkSpeed * NewPercent;
	MaxCustomMovementSpeed = BaseMaxCustomMovementSpeed * NewPercent;
	MaxFlySpeed = BaseMaxFlySpeed * NewPercent;
	MaxSwimSpeed = BaseMaxSwimSpeed * NewPercent;
	MaxWalkSpeedCrouched = BaseMaxWalkSpeedCrouched * NewPercent;
}
