// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WraithPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class WRAITH_API AWraithPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;
};
