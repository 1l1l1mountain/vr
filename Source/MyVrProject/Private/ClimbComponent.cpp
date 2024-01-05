// Fill out your copyright notice in the Description page of Project Settings.


#include "ClimbComponent.h"
#include "EnhancedInputComponent.h"
#include "MotionControllerComponent.h"
#include "VR_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values for this component's properties
UClimbComponent::UClimbComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UClimbComponent::BeginPlay()
{
	Super::BeginPlay();

	player = GetOwner<AVR_Player>();
	// ...
	
}


// Called every frame
void UClimbComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsLeftGrip || bIsRightGrip)
	{

		FVector currentHandLocation = bClimbHandLeft ? player->leftController->GetComponentLocation() : player->rightController->GetComponentLocation();
		
		FVector delta = currentHandLocation - prevHandLoc;
		delta.Normalize();
		prevHandLoc = currentHandLocation;
		
		player->GetCharacterMovement()->GravityScale = 0;

		UE_LOG(LogTemp, Warning, TEXT("CURRENT HAND : %s"), bClimbHandLeft ? *FString("Left") : *FString("Right"));
		UE_LOG(LogTemp, Warning, TEXT("delta x : %f, y : %f , z: %f"), delta.X, delta.Y ,delta.Z);
		player->AddActorWorldOffset(delta * -1*30);
	}
	else
	{

		//player->GetCharacterMovement()->GravityScale = 1.0f;

	}




	// ...
}

void UClimbComponent::SetupPlayerInputComponent(UEnhancedInputComponent* enhancedInputComponent, TArray<UInputAction*> inputs)
{//13, 14

	enhancedInputComponent->BindAction(inputs[13],ETriggerEvent::Started, this, &UClimbComponent::ClimbGrabLeft);
	enhancedInputComponent->BindAction(inputs[13],ETriggerEvent::Completed, this, &UClimbComponent::ClimbGrabLeft);
	enhancedInputComponent->BindAction(inputs[14],ETriggerEvent::Started, this, &UClimbComponent::ClimbGrabRight);
	enhancedInputComponent->BindAction(inputs[14],ETriggerEvent::Completed, this, &UClimbComponent::ClimbGrabRight);
}

void UClimbComponent::ClimbGrabLeft(const FInputActionValue& value)
{
	if (GrabHandleCheck(player->leftController))
	{


		bIsLeftGrip = value.Get<bool>();
		bClimbHandLeft = true;

			if (bIsLeftGrip)
			{
				prevHandLoc = player->leftController->GetComponentLocation();
			}

	}

}

void UClimbComponent::ClimbGrabRight(const FInputActionValue& value)
{
	
	if (GrabHandleCheck(player->rightController))
	{
		UE_LOG(LogTemp, Warning, TEXT("Collide Handle Right!"));
		bIsRightGrip = value.Get<bool>();
		bClimbHandLeft = false;
		if (bIsRightGrip)
		{
			prevHandLoc = player->rightController->GetComponentLocation();
		}

	}

}

bool UClimbComponent::GrabHandleCheck(UMotionControllerComponent* hand)
{
	FVector startLoc = hand->GetComponentLocation();
	FHitResult hitInfo;
	FCollisionObjectQueryParams params;
	params.AddObjectTypesToQuery(ECC_GameTraceChannel4);
	//sweep은 발사 되는거라 같은 지점으로 하면 모양만 생기나봄
	return GetWorld()->SweepSingleByObjectType(hitInfo, startLoc, startLoc, FQuat::Identity, params, FCollisionShape::MakeSphere(15));//반지름이 15센티

}

