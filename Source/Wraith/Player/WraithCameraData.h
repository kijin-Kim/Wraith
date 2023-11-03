// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WraithCameraData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class WRAITH_API UWraithCameraData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Camera)
	float TargetArmLength;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Camera)
	FVector SocketOffset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Camera)
	FVector TargetOffset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Camera)
	float FieldOfView;
};
