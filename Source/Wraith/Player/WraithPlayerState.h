// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerState.h"
#include "Wraith/AbilitySystem/WraithAbilitySystemComponent.h"
#include "WraithPlayerState.generated.h"

class UWraithAttributeSet;
class UWraithAbilitySystemComponent;
/**
 * 
 */

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

private:
	UPROPERTY()
	TObjectPtr<UWraithAttributeSet> AttributeSet;
	UPROPERTY()
	TObjectPtr<UWraithAbilitySystemComponent> AbilitySystemComponent;


	// TODO: TeamID 정하기
	FGenericTeamId TeamID;
};
