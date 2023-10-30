// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "WraithAbilitySystemComponent.generated.h"


class AWraithCharacter;
class UWraithAbilitySet;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WRAITH_API UWraithAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UWraithAbilitySystemComponent();
	
	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;
	virtual void AbilitySpecInputPressed(FGameplayAbilitySpec& Spec) override;
	virtual void AbilitySpecInputReleased(FGameplayAbilitySpec& Spec) override;
	
	void HandleAbilityInputs();
	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	FGameplayAbilitySpec* FindAbilitySpecFromDynamicTag(const FGameplayTag& Tag);

private:
	void InitializeAttribute(const APawn* AvatarPawn);
	void InitializeAbility();

private:
	TArray<FGameplayAbilitySpecHandle> PressedSpecHandles;
	TArray<FGameplayAbilitySpecHandle> HeldSpecHandles;
	TArray<FGameplayAbilitySpecHandle> ReleasedSpecHandles;
};
