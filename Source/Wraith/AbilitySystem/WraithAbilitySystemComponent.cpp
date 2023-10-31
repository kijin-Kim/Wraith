// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithAbilitySystemComponent.h"
#include "Ability/WraithGameplayAbility.h"
#include "Wraith/Character/WraithCharacterDescription.h"


UWraithAbilitySystemComponent::UWraithAbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWraithAbilitySystemComponent::AbilitySpecInputPressed(FGameplayAbilitySpec& Spec)
{
	Super::AbilitySpecInputPressed(Spec);
	// WaitInputPressed Event를 위하여 처리해줘야함.
	if (Spec.IsActive())
	{
		InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle, Spec.ActivationInfo.GetActivationPredictionKey());
	}
}

void UWraithAbilitySystemComponent::AbilitySpecInputReleased(FGameplayAbilitySpec& Spec)
{
	Super::AbilitySpecInputReleased(Spec);
	// WaitInputReleased Event를 위하여 처리해줘야함.
	if (Spec.IsActive())
	{
		InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, Spec.Handle, Spec.ActivationInfo.GetActivationPredictionKey());
	}
}

void UWraithAbilitySystemComponent::HandleAbilityInputs()
{
	TArray<FGameplayAbilitySpecHandle> AbilityHandlesToActivate;

	for (FGameplayAbilitySpecHandle Handle : HeldSpecHandles)
	{
		if (const FGameplayAbilitySpec* Spec = FindAbilitySpecFromHandle(Handle))
		{
			if (!Spec->IsActive())
			{
				AbilityHandlesToActivate.AddUnique(Handle);
			}
		}
	}

	for (FGameplayAbilitySpecHandle Handle : PressedSpecHandles)
	{
		if (FGameplayAbilitySpec* Spec = FindAbilitySpecFromHandle(Handle))
		{
			// 실행하고 있지 않을때만 
			if (!Spec->IsActive())
			{
				AbilityHandlesToActivate.AddUnique(Handle);
			}
			else // 이미 실행하고 있다면 Event를 넘겨줌.
			{
				AbilitySpecInputPressed(*Spec);
			}
		}
	}


	for (const FGameplayAbilitySpecHandle Handle : AbilityHandlesToActivate)
	{
		TryActivateAbility(Handle);
	}


	for (const FGameplayAbilitySpecHandle Handle : ReleasedSpecHandles)
	{
		if (FGameplayAbilitySpec* Spec = FindAbilitySpecFromHandle(Handle))
		{
			// 실행하고 있으면 Event를 넘겨줌 
			if (Spec->IsActive())
			{
				AbilitySpecInputReleased(*Spec);
			}
		}
	}


	PressedSpecHandles.Reset();
	ReleasedSpecHandles.Reset();
}

void UWraithAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromDynamicTag(InputTag);
	if (!AbilitySpec)
	{
		return;
	}

	const UWraithGameplayAbility* WraithGameplayAbility = Cast<UWraithGameplayAbility>(AbilitySpec->Ability);
	if (!WraithGameplayAbility)
	{
		return;
	}

	if (WraithGameplayAbility->InputEventPolicy == EWraithAbilityInputEventPolicy::Pressed || WraithGameplayAbility->InputEventPolicy == EWraithAbilityInputEventPolicy::Held)
	{
		PressedSpecHandles.AddUnique(AbilitySpec->Handle);
		HeldSpecHandles.AddUnique(AbilitySpec->Handle);
	}
}

void UWraithAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromDynamicTag(InputTag);
	if (!AbilitySpec)
	{
		return;
	}

	const UWraithGameplayAbility* WraithGameplayAbility = Cast<UWraithGameplayAbility>(AbilitySpec->Ability);
	if (!WraithGameplayAbility)
	{
		return;
	}

	ReleasedSpecHandles.AddUnique(AbilitySpec->Handle);
	HeldSpecHandles.Remove(AbilitySpec->Handle);
}

FGameplayAbilitySpec* UWraithAbilitySystemComponent::FindAbilitySpecFromDynamicTag(const FGameplayTag& Tag)
{
	for (auto& AbilitySpec : ActivatableAbilities.Items)
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(Tag))
		{
			return &AbilitySpec;
		}
	}
	return nullptr;
}

void UWraithAbilitySystemComponent::SetupAbilitySystem(const TArray<FWraithGameplayAbilityConfig>& GrantedAbilities,
                                                       const TArray<FWraithGameplayEffectConfig>& GrantedGameplayEffects)
{
	for (const auto& [AbilityClass, Level, InputTag] : GrantedAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = {AbilityClass, Level};
		if (AbilityActorInfo->IsLocallyControlledPlayer())
		{
			AbilitySpec.DynamicAbilityTags.AddTag(InputTag);
		}
		GiveAbility(AbilitySpec);
	}

	for (auto& [EffectClass, Level] : GrantedGameplayEffects)
	{
		FGameplayEffectContextHandle EffectContext = MakeEffectContext();
		EffectContext.AddSourceObject(GetOwner());
		const FGameplayEffectSpecHandle EffectSpec = MakeOutgoingSpec(EffectClass, Level, EffectContext);
		ApplyGameplayEffectSpecToSelf(*EffectSpec.Data);
	}
}