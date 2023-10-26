// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "WraithPlayerData.h"
#include "GameFramework/PlayerState.h"
#include "Wraith/AbilitySystem/WraithAbilitySystemComponent.h"
#include "WraithPlayerState.generated.h"

class UWraithPlayerData;
class UWraithAttributeSet;
class UWraithAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class WRAITH_API AWraithPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AWraithPlayerState();

	void SetPlayerData(const UWraithPlayerData* InWraithPlayerData);
	UWraithAbilitySystemComponent* GetWraithAbilitySystemComponent() const { return AbilitySystemComponent; }
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UWraithAttributeSet* GetWraithAttributeSet() const { return AttributeSet; }
	UAttributeSet* GetAttributeSet() const;
	const UWraithPlayerData* GetPlayerData() const { return PlayerData; }

protected:
	UPROPERTY(BlueprintReadOnly,  Category = "Player")
	TObjectPtr<const UWraithPlayerData> PlayerData;
	UPROPERTY(BlueprintReadOnly, Category = "Ability")
	TObjectPtr<UWraithAttributeSet> AttributeSet;
	UPROPERTY(BlueprintReadOnly, Category = "Ability")
	TObjectPtr<UWraithAbilitySystemComponent> AbilitySystemComponent;
};
