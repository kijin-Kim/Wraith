// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "WraithExtensionComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Wraith/AbilitySystem/WraithAttributeSet.h"
#include "Wraith/Player/WraithPlayerState.h"


// Sets default values
AWraithCharacter::AWraithCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	WraithExtensionComponent = CreateDefaultSubobject<UWraithExtensionComponent>(TEXT("WraithExtension"));
}

UWraithAbilitySystemComponent* AWraithCharacter::GetWraithAbilitySystemComponent() const
{
	return GetPlayerState<AWraithPlayerState>()->GetWraithAbilitySystemComponent();
}

UAbilitySystemComponent* AWraithCharacter::GetAbilitySystemComponent() const
{
	return GetWraithAbilitySystemComponent();
}

UWraithAttributeSet* AWraithCharacter::GetWraithAttributeSet() const
{
	return GetPlayerState<AWraithPlayerState>()->GetWraithAttributeSet();
}

UAttributeSet* AWraithCharacter::GetAttributeSet() const
{
	return GetWraithAttributeSet();
}
