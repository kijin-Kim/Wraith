


#include "WraithPawn.h"

#include "Wraith/AI/WraithAIController.h"
#include "Wraith/Character/WraithExtensionComponent.h"
#include "Wraith/Input/WraithEnhancedInputComponent.h"


AWraithPawn::AWraithPawn()
{
	OverrideInputComponentClass = UWraithEnhancedInputComponent::StaticClass();
	AIControllerClass = AWraithAIController::StaticClass();
	PrimaryActorTick.bCanEverTick = false;
	ExtensionComponent = CreateDefaultSubobject<UWraithExtensionComponent>(TEXT("WraithExtension"));
}
