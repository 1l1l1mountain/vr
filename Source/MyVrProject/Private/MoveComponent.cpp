// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"
#include "EnhancedInputComponent.h"
#include "VR_Player.h"
#include "MotionControllerComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "VRDrawFunctionLibrary.h"
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

void UMoveComponent::SetupPlayerInputComponent(UEnhancedInputComponent* enhancedInputComponent, TArray<UInputAction*> inputs)
{
	if (player != nullptr)
	{
		enhancedInputComponent->BindAction(inputs[0], ETriggerEvent::Triggered, this, &UMoveComponent::ShowLine);
		enhancedInputComponent->BindAction(inputs[0], ETriggerEvent::Triggered, this, &UMoveComponent::Teleport);
	}

}

void UMoveComponent::ShowLine(const FInputActionValue& value)
{
	
	bool bIsPressed = value.Get<bool>();

	player->leftLog->SetText(FText::FromString(FString::Printf(TEXT("%s"), bIsPressed ? *FString("Pressed!") : *FString("Released..."))));

	if (bIsPressed && player!= nullptr)
	{

		DrawTrajectory(player->leftController->GetComponentLocation(),player->leftHand->GetForwardVector()* -1  + player->leftHand->GetRightVector(),lineSpeed,50,0.1f);

	}
}
// 예측 선을 계산하고 그리는 함수 (중력 방식)
void UMoveComponent::DrawTrajectory(FVector startLoc, FVector dir, float speed, int32 segment, float interval)
{
	
	// dir 방향으로 segment 회수만큼 interval 간격(초)으로 반복해서 이동했을 위치를 계산한다.
	// 걔산 결과 값들은 배열 변수에 담아놓는다.
	TArray<FVector> linePositions; //배열의 사용법
	for (int32 i = 0;i < segment;i++)
	{
		float elapsedTime = interval * i;
		FVector gravityVec = FVector(0,0,GetWorld()->GetDefaultGravityZ());
		FVector newLocation = startLoc + dir * speed * elapsedTime + (0.5f * gravityVec * elapsedTime * elapsedTime );
		
		FHitResult hitInfo;
		
			if (i > 0 && GetWorld()->LineTraceSingleByChannel(hitInfo, linePositions[i - 1], newLocation, ECC_Visibility))
			{
				player->leftLog->SetText(FText::FromString(hitInfo.GetActor()->GetActorNameOrLabel()));

				linePositions.Add(hitInfo.ImpactPoint);
				break;
			}

				//계산 결과값들은 배열 변수에 담는다.
				linePositions.Add(newLocation);
					
			

	}

	// 계산된 위치를 선으로 연결해서 그린다.
	for (int32 i = 0;i < linePositions.Num() - 1; i++) //점으로 선을 만들면 개수 -1 
	{
		DrawDebugLine(GetWorld(),linePositions[i], linePositions[i+1],FColor::Green,false , 0 , 0 , 2.0f);
	}

	//마지막 위치에 빨강 상자를 표시한다.
	targetLocation = linePositions[linePositions.Num() - 1];
	DrawDebugSolidBox(GetWorld(), targetLocation, FVector(5), FColor::Red);
}

void UMoveComponent::DrawTrajectoryBezier(FVector startLoc, FVector dir, int32 segment)
{

	//????? 화요일 까지 과제
	//TArray<FVector> results = UVRDrawFunctionLibrary::CalculateBezierCurve(); 힌트
}

// 목표 지점으로 순간 이동하는 함수
void UMoveComponent::Teleport()
{
	// Black Fade In 효과를 준다.
	player->GetController<APlayerController>()->PlayerCameraManager->StartCameraFade(0,1.0f,teleportDelay,FLinearColor::Black);

	if (!targetLocation.IsNearlyZero())
	{
		FTimerHandle teleportTimer;
		GetWorld()->GetTimerManager().SetTimer(teleportTimer, FTimerDelegate::CreateLambda([&]() {

			player->SetActorLocation(targetLocation + FVector(0, 0, player->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
		}), teleportDelay, false);
	}

}

