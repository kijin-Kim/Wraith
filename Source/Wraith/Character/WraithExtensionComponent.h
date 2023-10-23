// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "WraithExtensionComponent.generated.h"


struct FGameplayTag;
class UPlayerMappableInputConfig;
class AWraithCharacter;

UCLASS(BlueprintType, meta=(BlueprintSpawnableComponent))
class WRAITH_API UWraithExtensionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWraithExtensionComponent();
	virtual void InitializeComponent() override;
	virtual void DestroyComponent(bool bPromoteChildren) override;

private:
	void BindDefaultInput();
	UFUNCTION()
	void OnWraithCharacterRestart(APawn* Pawn);
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void InputAbilityPressed(FGameplayTag InputTag);
	void InputAbilityReleased(FGameplayTag InputTag);

private:
	UPROPERTY()
	TObjectPtr<AWraithCharacter> WraithCharacterOwner;
};
