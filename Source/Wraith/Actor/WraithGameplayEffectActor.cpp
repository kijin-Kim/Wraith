// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithGameplayEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"


// Sets default values
AWraithGameplayEffectActor::AWraithGameplayEffectActor()
{
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Scene"));
}

void AWraithGameplayEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AWraithGameplayEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> EffectClass)
{
	check(EffectClass);
	UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);
	if(!ASC)
	{
		return;
	}
	
	FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpec = ASC->MakeOutgoingSpec(EffectClass, 1.0f, EffectContext);
	ASC->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data);
}
