// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithExtensionComponent.h"

#include "AbilitySystemGlobals.h"
#include "EnhancedInputSubsystems.h"
#include "WraithCharacter.h"
#include "WraithCharacterDescription.h"
#include "WraithCharacterMovementComponent.h"
#include "Wraith/WraithBlueprintFunctionLibrary.h"
#include "Wraith/WraithNativeGameplayTag.h"
#include "Wraith/Input/WraithEnhancedInputComponent.h"
#include "Wraith/Input/WraithInputConfig.h"
#include "Wraith/Player/WraithPlayerController.h"
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
	UWraithAbilitySystemComponent* WraithASC = UWraithBlueprintFunctionLibrary::GetWraithAbilitySystemComponent(GetOwner());
	check(WraithASC);
	APlayerState* PlayerState = WraithCharacterOwner->GetPlayerState();
	check(PlayerState);

	if (!WraithASC || !PlayerState)
	{
		return;
	}

	WraithASC->InitAbilityActorInfo(PlayerState, WraithCharacterOwner);

	if (CharacterDescription)
	{
		WraithASC->SetupAbilitySystem(CharacterDescription->GrantedAbilities, CharacterDescription->GrantedGameplayEffects);
		WraithCharacterOwner->GetMesh()->SetSkeletalMeshAsset(CharacterDescription->SkeletalMesh);
	}

	UWraithCharacterMovementComponent* WraithCharacterMovementComponent = CastChecked<UWraithCharacterMovementComponent>(WraithCharacterOwner->GetMovementComponent());
	WraithCharacterMovementComponent->InitializeWithAbilitySystemComponent();

	if (WraithCharacterOwner->IsPlayerControlled())
	{
		BindDefaultInput();
	}
}

void UWraithExtensionComponent::BindDefaultInput()
{
	const AWraithPlayerController* WraithPlayerController = WraithCharacterOwner->GetController<AWraithPlayerController>();
	check(WraithPlayerController);

	const ULocalPlayer* LocalPlayer = WraithPlayerController->GetLocalPlayer();
	check(LocalPlayer)

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(EnhancedInputLocalPlayerSubsystem);

	UWraithEnhancedInputComponent* WraithEnhancedInputComponent = CastChecked<UWraithEnhancedInputComponent>(WraithCharacterOwner->InputComponent);

	const UWraithInputConfig* InputConfig = WraithPlayerController->GetInputConfig();
	if (!InputConfig)
	{
		return;
	}

	WraithEnhancedInputComponent->BindNativeInputAction(InputConfig, WraithNativeGameplayTag::Input_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
	WraithEnhancedInputComponent->BindNativeInputAction(InputConfig, WraithNativeGameplayTag::Input_Look, ETriggerEvent::Triggered, this, &ThisClass::Look);
	WraithEnhancedInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::InputAbilityPressed, &ThisClass::InputAbilityReleased);

	for (auto& [Context, Priority] : InputConfig->InputMappingContexts)
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
	if (UWraithAbilitySystemComponent* WraithAbilitySystemComponent = Cast<UWraithAbilitySystemComponent>(
		UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(WraithCharacterOwner)))
	{
		WraithAbilitySystemComponent->AbilityInputTagPressed(InputTag);
	}
}

void UWraithExtensionComponent::InputAbilityReleased(FGameplayTag InputTag)
{
	if (UWraithAbilitySystemComponent* WraithAbilitySystemComponent = Cast<UWraithAbilitySystemComponent>(
		UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(WraithCharacterOwner)))
	{
		WraithAbilitySystemComponent->AbilityInputTagReleased(InputTag);
	}
}
