// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"


// Sets default values
AWraithAIController::AWraithAIController()
{
	PrimaryActorTick.bCanEverTick = false;
	bWantsPlayerState = true;

	BrainComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
}
