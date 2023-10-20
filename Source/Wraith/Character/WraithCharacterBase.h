// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "WraithCharacterBase.generated.h"


class UWraithAttributeSet;
class UAttributeSet;
class UWraithAbilitySystemComponent;
class USpringArmComponent;
class UCameraComponent;
class UCameraComponent;
class UInputMappingContext;


UCLASS(config=Game)
class AWraithCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AWraithCharacterBase();

public:
	virtual UWraithAbilitySystemComponent* GetWraithAbilitySystemComponent() const { return AbilitySystemComponent; }
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UWraithAttributeSet* GetWraithAttributeSet() const { return AttributeSet; }
	virtual UAttributeSet* GetAttributeSet() const;

protected:
	void InitializeAbilitySystem(AActor* OwnerActor, AActor* AvatarActor) const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Ability")
	TObjectPtr<UWraithAttributeSet> AttributeSet;
	UPROPERTY(BlueprintReadOnly, Category = "Ability")
	TObjectPtr<UWraithAbilitySystemComponent> AbilitySystemComponent;
};
