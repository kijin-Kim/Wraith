// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "WraithCharacterDescription.h"
#include "Components/ActorComponent.h"
#include "WraithExtensionComponent.generated.h"


class AWraithCharacter;
class UWraithCharacterDescription;

UCLASS(BlueprintType, meta=(BlueprintSpawnableComponent))
class WRAITH_API UWraithExtensionComponent : public UActorComponent
{
	GENERATED_BODY()

	friend class AWraithGameMode;
public:
	UWraithExtensionComponent();
	virtual void InitializeComponent() override;
	void InitializeWraithExtension();

	const UWraithCharacterDescription* GetCharacterDescription() const { return CharacterDescription; }

private:
	void BindDefaultInput();

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void InputAbilityPressed(FGameplayTag InputTag);
	void InputAbilityReleased(FGameplayTag InputTag);

private:
	UPROPERTY()
	TObjectPtr<AWraithCharacter> WraithCharacterOwner;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<const UWraithCharacterDescription> CharacterDescription;
};
