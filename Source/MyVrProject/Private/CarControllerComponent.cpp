// Fill out your copyright notice in the Description page of Project Settings.


#include "CarControllerComponent.h"
#include "VR_Player.h"
#include "EnhancedInputComponent.h"


// Sets default values for this component's properties
UCarControllerComponent::UCarControllerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	player = GetOwner<AVR_Player>();
}


// Called when the game starts
void UCarControllerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCarControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

