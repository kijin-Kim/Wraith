// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithExtensionComponent.h"

#include "AbilitySystemGlobals.h"
#include "EnhancedInputSubsystems.h"
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
	PawnOwner = GetOwner<APawn>();
	check(PawnOwner);
}

void UWraithExtensionComponent::InitializeWraithExtension()
{
	UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(PawnOwner);
	APlayerState* PlayerState = PawnOwner->GetPlayerState();
	if (AbilitySystemComponent && PlayerState)
	{
		AbilitySystemComponent->InitAbilityActorInfo(PlayerState, PawnOwner);
	}

	if (PawnOwner->IsPlayerControlled())
	{
		BindDefaultInput();
	}
}

void UWraithExtensionComponent::BindDefaultInput()
{
	const APlayerController* PlayerController = PawnOwner->GetController<APlayerController>();
	check(PlayerController);

	const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	check(LocalPlayer)

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(EnhancedInputLocalPlayerSubsystem);

	UWraithEnhancedInputComponent* WraithEnhancedInputComponent = Cast<UWraithEnhancedInputComponent>(PawnOwner->InputComponent);
	check(WraithEnhancedInputComponent);

	const AWraithPlayerState* WraithPlayerState = PlayerController->GetPlayerState<AWraithPlayerState>();
	check(WraithPlayerState);
	const UWraithPlayerData* WraithPlayerData = WraithPlayerState->GetPlayerData();
	if (!WraithPlayerData || !WraithPlayerData->InputConfig)
	{
		return;
	}

	WraithEnhancedInputComponent->BindNativeInputAction(WraithPlayerData->InputConfig, WraithNativeGameplayTag::Input_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
	WraithEnhancedInputComponent->BindNativeInputAction(WraithPlayerData->InputConfig, WraithNativeGameplayTag::Input_Look, ETriggerEvent::Triggered, this, &ThisClass::Look);
	WraithEnhancedInputComponent->BindAbilityActions(WraithPlayerData->InputConfig, this, &ThisClass::InputAbilityPressed, &ThisClass::InputAbilityReleased);

	UEnhancedInputUserSettings* UserSettings = EnhancedInputLocalPlayerSubsystem->GetUserSettings();

	for (auto& [Context, Priority] : WraithPlayerData->InputConfig->InputMappingContexts)
	{
		FModifyContextOptions Option;
		Option.bIgnoreAllPressedKeysUntilRelease = false;
		Option.bForceImmediately = true;
		EnhancedInputLocalPlayerSubsystem->AddMappingContext(Context, Priority, Option);
	}
}


void UWraithExtensionComponent::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	AController* Controller = PawnOwner->GetController();
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		PawnOwner->AddMovementInput(ForwardDirection, MovementVector.Y);
		PawnOwner->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void UWraithExtensionComponent::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	APlayerController* PlayerController = PawnOwner->GetController<APlayerController>();
	if (PlayerController != nullptr)
	{
		PlayerController->AddYawInput(LookAxisVector.X);
		PlayerController->AddPitchInput(LookAxisVector.Y);
	}
}

void UWraithExtensionComponent::InputAbilityPressed(FGameplayTag InputTag)
{
	if (UWraithAbilitySystemComponent* WraithAbilitySystemComponent = Cast<UWraithAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(PawnOwner)))
	{
		WraithAbilitySystemComponent->AbilityInputTagPressed(InputTag);
	}
}

void UWraithExtensionComponent::InputAbilityReleased(FGameplayTag InputTag)
{
	if (UWraithAbilitySystemComponent* WraithAbilitySystemComponent = Cast<UWraithAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(PawnOwner)))
	{
		WraithAbilitySystemComponent->AbilityInputTagReleased(InputTag);
	}
}
