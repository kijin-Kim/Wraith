// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithInputConfig.h"

UInputAction* UWraithInputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag)
{
	for(auto& [InputAction, InputTag] : NativeInputActions)
	{
		if(InputAction && InputTag == InInputTag)
		{
			return InputAction;
		}
	}

	return nullptr;
}
