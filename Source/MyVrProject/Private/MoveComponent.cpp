// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"
#include "EnhancedInputComponent.h"
#include "VR_Player.h"
#include "MotionControllerComponent.h"

// Sets default values for this component's properties
UMoveComponent::UMoveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	player = GetOwner<AVR_Player>();
}


// Called every frame
void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMoveComponent::SetupPlayerInputComponent(UEnhancedInputComponent* enhancedInputComponent)
{
	if (player != nullptr)
	{
		enhancedInputComponent->BindAction(player->ia_rightTriggerBool,ETriggerEvent::Triggered, this, &UMoveComponent::ShowLine);

	}

}

void UMoveComponent::ShowLine(const FInputActionValue& value)
{
	bool bIsPressed = value.Get<bool>();
	if (bIsPressed && player!= nullptr)
	{

		DrawTrajectory(player->leftController->GetComponentLocation(),player->leftController->GetForwardVector() + player->leftController->GetUpVector(),100,50,0.1f);

	}
}

void UMoveComponent::DrawTrajectory(FVector startLoc, FVector dir, float speed, int32 segment, float interval)
{
	
	// dir �������� segment ȸ����ŭ interval ����(��)���� �ݺ��ؼ� �̵����� ��ġ�� ����Ѵ�.
	// �»� ��� ������ �迭 ������ ��Ƴ��´�.
	TArray<FVector> linePositions; //�迭�� ����
	for (int32 i = 0;i < segment;i++)
	{
		float elapsedTime = interval * i;
	
		FVector newLocation = startLoc + dir * speed * elapsedTime - (0.5f * GetWorld()->GetGravityZ() * elapsedTime * elapsedTime );
		linePositions.Add(newLocation);

	}

	// ���� ��ġ�� ������ �����ؼ� �׸���.
	for (int32 i = 0;i < linePositions.Num() - 1; i++)
	{
		DrawDebugLine(GetWorld(),linePositions[i], linePositions[i+1],FColor::Green);
	}


}

