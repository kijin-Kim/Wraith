// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "WraithCharacter.generated.h"


class UAttributeSet;
class UWraithExtensionComponent;
class UCameraComponent;
class USpringArmComponent;
class UWraithAttributeSet;
class UWraithAbilitySystemComponent;

UCLASS()
class WRAITH_API AWraithCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AWraithCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void NotifyRestarted() override;
	USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	virtual UWraithAbilitySystemComponent* GetWraithAbilitySystemComponent() const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UWraithAttributeSet* GetWraithAttributeSet() const;
	virtual UAttributeSet* GetAttributeSet() const;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWraithExtensionComponent> WraithExtensionComponent;
	
};
