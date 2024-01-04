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

	//����� ��ư�� �� �� ������ ��
	if (bIsLeftGrip && bIsRightGrip)
	{
		float degree = GetControllerAngle(player->leftController->GetComponentLocation(), player->rightController->GetComponentLocation(), player->GetActorRightVector());
	
		//�α� ǥ��
		player->leftLog->SetText(FText::FromString(FString::Printf(TEXT("Angle: %d"), (int32)degree)));
	
		//���� ȸ����Ű��
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

//���� ���� ���͸� �̿��ؼ� �޼հ� �������� ���� ���̸� ����ؼ� ��ȯ�ϴ� �Լ�
float UCarControllerComponent::GetControllerAngle(FVector leftControllerLoc, FVector rightControllerLoc, FVector baseDirection)
{
	FVector handVector = (rightControllerLoc - leftControllerLoc).GetSafeNormal();
	FVector baseVector = baseDirection.GetSafeNormal();

	float dotResult = FVector::DotProduct(handVector, baseVector); //�ڻ��� ��Ÿ�� ��
	//���Լ� ���ؾ���. �Ǵ� �и� ���� ���缭 ���
	float degree  = FMath::RadiansToDegrees(FMath::Acos(dotResult));

	//���� ���Ϳ� ������ ����� ����̸� �������� ���� �ö� ����, ������ �������� �Ʒ��� ������ ����
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
