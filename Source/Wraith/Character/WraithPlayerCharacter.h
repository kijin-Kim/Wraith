// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WraithCharacterBase.h"
#include "WraithPlayerCharacter.generated.h"


class UInputAction;

UCLASS()
class WRAITH_API AWraithPlayerCharacter : public AWraithCharacterBase
{
	GENERATED_BODY()

public:
	AWraithPlayerCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	virtual UWraithAbilitySystemComponent* GetWraithAbilitySystemComponent() const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UWraithAttributeSet* GetWraithAttributeSet() const override;
	virtual UAttributeSet* GetAttributeSet() const override;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;
};
