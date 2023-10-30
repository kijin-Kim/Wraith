// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GenericTeamAgentInterface.h"
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

USTRUCT(BlueprintType)
struct FAttributeInitData
{
	GENERATED_BODY()

	bool IsValid() const
	{
		return PrimaryAttributeInitializer && SecondaryAttributeObserver;
	}

	// Primary Attribute값을 초기화하는 GameplayEffect
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> PrimaryAttributeInitializer;
	// Primary Attribute의 변화에 따라 Secondary Attribute을 계속해서 변화시키는 GameplayEffect
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> SecondaryAttributeObserver;
};


UCLASS()
class WRAITH_API AWraithPlayerState : public APlayerState, public IAbilitySystemInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AWraithPlayerState();
	
	virtual void SetGenericTeamId(const FGenericTeamId& InTeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;
	
	UWraithAbilitySystemComponent* GetWraithAbilitySystemComponent() const { return AbilitySystemComponent; }
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UWraithAttributeSet* GetWraithAttributeSet() const { return AttributeSet; }
	UAttributeSet* GetAttributeSet() const;
	const FAttributeInitData& GetAttributeInitData() const { return AttributeInitData; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
	FAttributeInitData AttributeInitData;
	UPROPERTY(BlueprintReadOnly, Category = "Ability")
	TObjectPtr<UWraithAttributeSet> AttributeSet;
	UPROPERTY(BlueprintReadOnly, Category = "Ability")
	TObjectPtr<UWraithAbilitySystemComponent> AbilitySystemComponent;


	// TODO: TeamID 정하기
	FGenericTeamId TeamID;
};
