// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "WraithBlueprintFunctionLibrary.generated.h"

class UWraithCameraData;
class UWraithAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class WRAITH_API UWraithBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category="WraithBlueprintFunctionLibrary|AbilitySystem", meta = (DefaultToSelf = "WorldContextObject"))
	static UWraithAbilitySystemComponent* GetWraithAbilitySystemComponent(const UObject* WorldContextObject);
	UFUNCTION(BlueprintCallable, Category="WraithBlueprintFunctionLibrary|PlayerCameraData")
	static void SetTargetActorCameraData(AWraithCharacter* WraithCharacter, const UWraithCameraData* CameraData);

	
};
