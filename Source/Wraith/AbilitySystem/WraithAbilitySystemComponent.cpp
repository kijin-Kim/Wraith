// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithAbilitySystemComponent.h"

#include "WraithAbilitySet.h"
#include "Ability/WraithGameplayAbility.h"
#include "Wraith/Player/WraithPlayerData.h"
#include "Wraith/Core/WraithWorldSettings.h"
#include "Wraith/Player/WraithPlayerState.h"


UWraithAbilitySystemComponent::UWraithAbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWraithAbilitySystemComponent::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)
{
	Super::InitAbilityActorInfo(InOwnerActor, InAvatarActor);

	// UAbilitySystemComponent::InitializeComponent에서 Default로 Outer(PlayerState)를 무시.
	if (const APawn* AvatarPawn = Cast<APawn>(InAvatarActor))
	{
		InitializeAttribute(AvatarPawn);
		InitializeAbility();
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
		AbilitySpec->InputPressed = true;
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

	AbilitySpec->InputPressed = false;
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

void UWraithAbilitySystemComponent::InitializeAttribute(const APawn* AvatarPawn)
{
	const AWraithPlayerState* PlayerState = AvatarPawn->GetPlayerState<AWraithPlayerState>();
	const FAttributeInitData& InitData = PlayerState->GetAttributeInitData();
	if (InitData.IsValid())
	{
		// 자신에게 GameplayEffect를 적용함으로써 Attribute의 초기값을 설정
		auto SetupAttributes = [&](TSubclassOf<UGameplayEffect> AttributeSetupEffectClass)
		{
			FGameplayEffectContextHandle EffectContext = MakeEffectContext();
			EffectContext.AddSourceObject(GetOwner());
			const FGameplayEffectSpecHandle EffectSpec = MakeOutgoingSpec(AttributeSetupEffectClass, 1.0f, EffectContext);
			ApplyGameplayEffectSpecToSelf(*EffectSpec.Data);
		};

		SetupAttributes(InitData.PrimaryAttributeInitializer);
		SetupAttributes(InitData.SecondaryAttributeObserver);
	}
}

void UWraithAbilitySystemComponent::InitializeAbility()
{
	const AWraithWorldSettings* WorldSettings = Cast<AWraithWorldSettings>(GetWorld()->GetWorldSettings());
	if (!WorldSettings || !WorldSettings->PlayerData || !WorldSettings->PlayerData->AbilitySet)
	{
		return;
	}

	// DataSet으로부터 초기 AbilitySet을 받아 Avatar에 부여
	UWraithAbilitySet* AbilitySet = WorldSettings->PlayerData->AbilitySet;
	for (const auto& [AbilityClass, Level, InputTag] : AbilitySet->GrantedAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = {AbilityClass, Level};
		if (AbilityActorInfo->IsLocallyControlledPlayer())
		{
			AbilitySpec.DynamicAbilityTags.AddTag(InputTag);
		}
		GiveAbility(AbilitySpec);
	}
}
