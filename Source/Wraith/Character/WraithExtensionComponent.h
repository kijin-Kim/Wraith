// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "WraithExtensionComponent.generated.h"


struct FGameplayTag;
class UPlayerMappableInputConfig;

UCLASS(BlueprintType, meta=(BlueprintSpawnableComponent))
class WRAITH_API UWraithExtensionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWraithExtensionComponent();
	virtual void InitializeComponent() override;
	void InitializeWraithExtension();

private:
	void BindDefaultInput();
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void InputAbilityPressed(FGameplayTag InputTag);
	void InputAbilityReleased(FGameplayTag InputTag);

private:
	UPROPERTY()
	TObjectPtr<APawn> PawnOwner;
};
