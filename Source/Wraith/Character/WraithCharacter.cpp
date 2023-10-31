// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithCharacter.h"

#include "WraithCharacterMovementComponent.h"
#include "WraithExtensionComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Wraith/AbilitySystem/AttributeSet/WraithAttributeSet.h"
#include "Wraith/AI/WraithAIController.h"
#include "Wraith/Input/WraithEnhancedInputComponent.h"
#include "Wraith/Player/WraithPlayerState.h"


AWraithCharacter::AWraithCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UWraithCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	OverrideInputComponentClass = UWraithEnhancedInputComponent::StaticClass();
	AIControllerClass = AWraithAIController::StaticClass();
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

	ExtensionComponent = CreateDefaultSubobject<UWraithExtensionComponent>(TEXT("WraithExtension"));
}

void AWraithCharacter::NotifyRestarted()
{
	Super::NotifyRestarted();
	ExtensionComponent->InitializeWraithExtension();
}

UWraithAbilitySystemComponent* AWraithCharacter::GetWraithAbilitySystemComponent() const
{
	const AWraithPlayerState* WraithPlayerState = GetPlayerState<AWraithPlayerState>();
	return WraithPlayerState ? WraithPlayerState->GetWraithAbilitySystemComponent() : nullptr;
}

UAbilitySystemComponent* AWraithCharacter::GetAbilitySystemComponent() const
{
	return GetWraithAbilitySystemComponent();
}

UWraithAttributeSet* AWraithCharacter::GetWraithAttributeSet() const
{
	const AWraithPlayerState* WraithPlayerState = GetPlayerState<AWraithPlayerState>();
	return WraithPlayerState ? WraithPlayerState->GetWraithAttributeSet() : nullptr;
}

UAttributeSet* AWraithCharacter::GetAttributeSet() const
{
	return GetWraithAttributeSet();
}
