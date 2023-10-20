// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WraithCharacterBase.h"
#include "WraithAICharacter.generated.h"

class UWraithAbilitySystemComponent;
class UWraithAttributeSet;


UCLASS()
class WRAITH_API AWraithAICharacter : public AWraithCharacterBase
{
	GENERATED_BODY()

public:
	AWraithAICharacter();
	virtual void BeginPlay() override;

	
};
