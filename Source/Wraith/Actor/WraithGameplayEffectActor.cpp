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

void AWraithGameplayEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	check(GameplayEffectClass);
	UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);
	if(!AbilitySystemComponent)
	{
		return;
	}
	
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpec = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, 1.0f, EffectContext);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data);
}
