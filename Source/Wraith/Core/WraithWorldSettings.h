

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "WraithWorldSettings.generated.h"

class UWraithPlayerData;
/**
 * 
 */
UCLASS()
class WRAITH_API AWraithWorldSettings : public AWorldSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UWraithPlayerData> PlayerData;
};
