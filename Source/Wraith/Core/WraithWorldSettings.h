

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "WraithWorldSettings.generated.h"

class UWraithGameDescription;
/**
 * 
 */
UCLASS()
class WRAITH_API AWraithWorldSettings : public AWorldSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<const UWraithGameDescription> DefaultGameDescription;
};
