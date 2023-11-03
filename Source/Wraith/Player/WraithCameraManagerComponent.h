// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WraithCameraManagerComponent.generated.h"


class USpringArmComponent;
class UCameraComponent;
class AWraithCharacter;
class UWraithCameraData;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WRAITH_API UWraithCameraManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWraithCameraManagerComponent();
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void SetCameraData(const UWraithCameraData* CameraData);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AWraithCharacter> WraithCharacter;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponent;
};
