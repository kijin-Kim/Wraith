// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithExtensionComponent.h"

#include "EnhancedInputSubsystems.h"
#include "PlayerMappableInputConfig.h"
#include "WraithCharacter.h"
#include "Wraith/WraithNativeGameplayTag.h"
#include "Wraith/Input/WraithEnhancedInputComponent.h"
#include "Wraith/Input/WraithInputConfig.h"
#include "Wraith/Player/WraithPlayerData.h"
#include "Wraith/Player/WraithPlayerState.h"


UWraithExtensionComponent::UWraithExtensionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UWraithExtensionComponent::InitializeComponent()
{
	Super::InitializeComponent();
	WraithCharacterOwner = GetOwner<AWraithCharacter>();
	check(WraithCharacterOwner);
}

void UWraithExtensionComponent::InitializeWraithExtension()
{
	AWraithPlayerState* WraithPlayerState = WraithCharacterOwner->GetPlayerStateChecked<AWraithPlayerState>();
	
	WraithCharacterOwner->GetAbilitySystemComponent()->InitAbilityActorInfo(WraithPlayerState, WraithCharacterOwner);
	if (!WraithPlayerState->IsABot())
	{
		BindDefaultInput();
	}
}

void UWraithExtensionComponent::BindDefaultInput()
{
	const APlayerController* PlayerController = WraithCharacterOwner->GetController<APlayerController>();
	check(PlayerController);

	const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	check(LocalPlayer)

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(EnhancedInputLocalPlayerSubsystem);

	UWraithEnhancedInputComponent* WraithEnhancedInputComponent = Cast<UWraithEnhancedInputComponent>(WraithCharacterOwner->InputComponent);
	check(WraithEnhancedInputComponent);

	const AWraithPlayerState* WraithPlayerState = PlayerController->GetPlayerState<AWraithPlayerState>();
	check(WraithPlayerState);
	const UWraithPlayerData* WraithPlayerData = WraithPlayerState->GetWraithPlayerData();
	check(WraithPlayerData)
	WraithEnhancedInputComponent->BindNativeInputAction(WraithPlayerData->WraithInputConfig, WraithNativeGameplayTag::Input_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
	WraithEnhancedInputComponent->BindNativeInputAction(WraithPlayerData->WraithInputConfig, WraithNativeGameplayTag::Input_Look, ETriggerEvent::Triggered, this, &ThisClass::Look);
	WraithEnhancedInputComponent->BindAbilityActions(WraithPlayerData->WraithInputConfig, this, &ThisClass::InputAbilityPressed, &ThisClass::InputAbilityReleased);

	for (const auto& InputConfig : WraithPlayerData->WraithInputConfig->PlayerMappableInputConfigs)
	{
		for (auto& [Context, Priority] : InputConfig->GetMappingContexts())
		{
			FModifyContextOptions Option;
			Option.bIgnoreAllPressedKeysUntilRelease = false;
			Option.bForceImmediately = true;
			EnhancedInputLocalPlayerSubsystem->AddMappingContext(Context, Priority, Option);
		}
	}
}


void UWraithExtensionComponent::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	AController* Controller = WraithCharacterOwner->GetController();
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		WraithCharacterOwner->AddMovementInput(ForwardDirection, MovementVector.Y);
		WraithCharacterOwner->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void UWraithExtensionComponent::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	APlayerController* PlayerController = WraithCharacterOwner->GetController<APlayerController>();
	if (PlayerController != nullptr)
	{
		PlayerController->AddYawInput(LookAxisVector.X);
		PlayerController->AddPitchInput(LookAxisVector.Y);
	}
}

void UWraithExtensionComponent::InputAbilityPressed(FGameplayTag InputTag)
{
	UWraithAbilitySystemComponent* WraithAbilitySystemComponent = WraithCharacterOwner->GetWraithAbilitySystemComponent();
	check(WraithAbilitySystemComponent);
	WraithAbilitySystemComponent->AbilityInputTagPressed(InputTag);
}

void UWraithExtensionComponent::InputAbilityReleased(FGameplayTag InputTag)
{
	UWraithAbilitySystemComponent* WraithAbilitySystemComponent = WraithCharacterOwner->GetWraithAbilitySystemComponent();
	check(WraithAbilitySystemComponent);
	WraithAbilitySystemComponent->AbilityInputTagReleased(InputTag);
}
