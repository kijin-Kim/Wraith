// Fill out your copyright notice in the Description page of Project Settings.
// This code is from lyra.

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
	void BindNativeInputAction(UWraithInputConfig* WraithInputConfig, const FGameplayTag& GameplayTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func);
};

template <class UserClass, typename FuncType>
void UWraithEnhancedInputComponent::BindNativeInputAction(UWraithInputConfig* WraithInputConfig, const FGameplayTag& GameplayTag, ETriggerEvent TriggerEvent, UserClass* Object,
                                                          FuncType Func)
{
	check(WraithInputConfig);
	if (UInputAction* InputAction = WraithInputConfig->FindNativeInputActionByTag(GameplayTag))
	{
		BindAction(InputAction, TriggerEvent, Object, Func);
	}
}
