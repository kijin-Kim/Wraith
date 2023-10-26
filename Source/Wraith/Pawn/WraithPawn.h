#pragma once

#include "CoreMinimal.h"

#include "WraithPawn.generated.h"

class UWraithExtensionComponent;

UCLASS()
class WRAITH_API AWraithPawn : public APawn
{
	GENERATED_BODY()

public:
	AWraithPawn();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWraithExtensionComponent> ExtensionComponent;
};
