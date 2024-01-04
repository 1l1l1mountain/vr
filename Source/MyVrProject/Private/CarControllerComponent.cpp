// Fill out your copyright notice in the Description page of Project Settings.


#include "CarControllerComponent.h"
#include "VR_Player.h"
#include "EnhancedInputComponent.h"
#include "MotionControllerComponent.h"
#include "Components/TextRenderComponent.h"
#include "MyCar.h"

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

	//양손의 버튼을 둘 다 눌렀을 때
	if (bIsLeftGrip && bIsRightGrip)
	{
		float degree = GetControllerAngle(player->leftController->GetComponentLocation(), player->rightController->GetComponentLocation(), player->GetActorRightVector());
	
		//로그 표시
		player->leftLog->SetText(FText::FromString(FString::Printf(TEXT("Angle: %d"), (int32)degree)));
	
		//차를 회전시키기
		player->controlledCar->RotateCar(degree);
	}

}

void UCarControllerComponent::SetupPlayerInputComponent(UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*>inputs)
{
	enhancedInputComponent->BindAction(inputs[3], ETriggerEvent::Started, this, &UCarControllerComponent::GripLeftOn);
	enhancedInputComponent->BindAction(inputs[3], ETriggerEvent::Completed, this, &UCarControllerComponent::GripLeftOff);
	enhancedInputComponent->BindAction(inputs[3], ETriggerEvent::Started, this, &UCarControllerComponent::GripRightOn);
	enhancedInputComponent->BindAction(inputs[3], ETriggerEvent::Completed, this, &UCarControllerComponent::GripRightOff);
}

//기준 방향 벡터를 이용해서 왼손과 오른손의 각도 차이를 계산해서 반환하는 함수
float UCarControllerComponent::GetControllerAngle(FVector leftControllerLoc, FVector rightControllerLoc, FVector baseDirection)
{
	FVector handVector = (rightControllerLoc - leftControllerLoc).GetSafeNormal();
	FVector baseVector = baseDirection.GetSafeNormal();

	float dotResult = FVector::DotProduct(handVector, baseVector); //코사인 세타의 값
	//역함수 구해야함. 또는 분모 분자 맞춰서 상쇄
	float degree  = FMath::RadiansToDegrees(FMath::Acos(dotResult));

	//위쪽 벡터와 내적한 결과가 양수이면 오른손이 위로 올라간 벡터, 음수면 오른손이 아래로 내려간 벡터
	if (FVector::DotProduct(player->GetActorUpVector(), handVector) > 0)
	{

		degree *= -1.0f;
	}




	return degree;
}

void UCarControllerComponent::GripLeftOn()
{
	bIsLeftGrip = true;
}

void UCarControllerComponent::GripLeftOff()
{
	bIsLeftGrip = false;

}

void UCarControllerComponent::GripRightOn()
{
	bIsRightGrip = true;
}

void UCarControllerComponent::GripRightOff()
{
	bIsRightGrip = false;

}
