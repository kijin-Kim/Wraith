// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithCameraManagerComponent.h"

#include "WraithCameraData.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Wraith/Character/WraithCharacter.h"


UWraithCameraManagerComponent::UWraithCameraManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWraithCameraManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	WraithCharacter = CastChecked<AWraithCharacter>(GetOwner());
	CameraComponent = WraithCharacter->GetFollowCamera();
	check(CameraComponent);
	SpringArmComponent = WraithCharacter->GetCameraBoom();
	check(SpringArmComponent);
}

void UWraithCameraManagerComponent::SetCameraData(const UWraithCameraData* CameraData)
{
	if (CameraData)
	{
		SpringArmComponent->TargetArmLength = CameraData->TargetArmLength;
		SpringArmComponent->SocketOffset = CameraData->SocketOffset;
		SpringArmComponent->TargetOffset = CameraData->TargetOffset;
		CameraComponent->SetFieldOfView(CameraData->FieldOfView);
	}
}
