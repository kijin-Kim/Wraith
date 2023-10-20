// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithAICharacter.h"


AWraithAICharacter::AWraithAICharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}
void AWraithAICharacter::BeginPlay()
{
	Super::BeginPlay();
	InitializeAbilitySystem(this, this);
}

