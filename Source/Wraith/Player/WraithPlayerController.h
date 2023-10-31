// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WraithPlayerController.generated.h"

class AWraithGameMode;
class UWraithInputConfig;
/**
 * 
 */
UCLASS()
class WRAITH_API AWraithPlayerController : public APlayerController
{
	GENERATED_BODY()

	friend AWraithGameMode;
public:
	AWraithPlayerController();
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;

	const UWraithInputConfig* GetInputConfig() const { return InputConfig; }

private:
	UPROPERTY()
	TObjectPtr<const UWraithInputConfig> InputConfig;
};
