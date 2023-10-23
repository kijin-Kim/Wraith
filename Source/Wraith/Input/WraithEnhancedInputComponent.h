// Fill out your copyright notice in the Description page of Project Settings.
// This code is from LyraStarterGame.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "WraithInputConfig.h"
#include "WraithEnhancedInputComponent.generated.h"


class UWraithInputConfig;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WRAITH_API UWraithEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	UWraithEnhancedInputComponent();

	template <class UserClass, typename FuncType>
	void BindNativeInputAction(const UWraithInputConfig* WraithInputConfig, const FGameplayTag& GameplayTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func);
	template <class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	void BindAbilityActions(const UWraithInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc);
};

template <class UserClass, typename FuncType>
void UWraithEnhancedInputComponent::BindNativeInputAction(const UWraithInputConfig* WraithInputConfig, const FGameplayTag& GameplayTag, ETriggerEvent TriggerEvent,
                                                          UserClass* Object,
                                                          FuncType Func)
{
	check(WraithInputConfig);
	if (UInputAction* InputAction = WraithInputConfig->FindNativeInputActionByTag(GameplayTag))
	{
		BindAction(InputAction, TriggerEvent, Object, Func);
	}
}

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType>
void UWraithEnhancedInputComponent::BindAbilityActions(const UWraithInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc)
{
	check(InputConfig);

	for (const FWraithInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, PressedFunc, Action.InputTag);
			}

			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
			}
		}
	}
}
