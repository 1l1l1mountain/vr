// Fill out your copyright notice in the Description page of Project Settings.


#include "VR_Player.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "MotionControllerComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Components/TextRenderComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
AVR_Player::AVR_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cameraComp->SetupAttachment(RootComponent);

	hmdMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HMD Mesh"));
	hmdMesh->SetupAttachment(cameraComp);

	leftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Left Controller"));
	leftController->SetupAttachment(RootComponent);
	leftController->SetRelativeLocation(FVector(50,-30,-10));
	leftController->SetTrackingMotionSource(FName("Left"));

	leftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Hand Mesh"));
	leftHand->SetupAttachment(leftController);
	leftHand->SetRelativeRotation(FRotator(-90,-45,-180));

	leftLog = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Left Log"));
	leftLog->SetupAttachment(leftHand);
	leftLog->SetRelativeLocation(FVector(-20, 10, 0));
	leftLog->SetRelativeRotation(FRotator(0,-90, -90));
	leftLog->SetHorizontalAlignment(EHTA_Center);
	leftLog->SetVerticalAlignment(EVRTA_TextCenter);
	leftLog->SetWorldSize(20);
	leftLog->SetTextRenderColor(FColor(255,255,0));


	rightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right Controller"));
	rightController->SetupAttachment(RootComponent);
	rightController->SetRelativeLocation(FVector(50, 30, -10));
	rightController->SetTrackingMotionSource(FName("Right"));

	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand Mesh"));
	rightHand->SetupAttachment(rightController);
	rightHand->SetRelativeRotation(FRotator(90, 45,0));

	rightLog = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Right Log"));
	rightLog->SetupAttachment(rightHand);
	rightLog->SetRelativeLocation(FVector(20, 10, 0));
	rightLog->SetRelativeRotation(FRotator(0, -90, 90));
	rightLog->SetHorizontalAlignment(EHTA_Center);
	rightLog->SetVerticalAlignment(EVRTA_TextCenter);
	rightLog->SetWorldSize(20);
	rightLog->SetTextRenderColor(FColor(255, 255, 0));




}

// Called when the game starts or when spawned
void AVR_Player::BeginPlay()
{
	Super::BeginPlay();
	
	//헤드 마운트 디스플레이 장비의 트래킹 (추적) 기준 위치를 Stage로 설정한다.
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Stage);

	// 입력 매핑 설정하기
	if (APlayerController* pc = GetWorld()->GetFirstPlayerController())
	{
		UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		if (subsys != nullptr && imc != nullptr)
		{
			subsys->AddMappingContext(imc, 0);
		}

	}
}

// Called every frame
void AVR_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVR_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//기존 입력 데이터를 Enhanced 입력 데이터 형태로 변환한다.
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (enhancedInputComponent != nullptr)
	{
		//입력 키 바인딩 하기
		enhancedInputComponent->BindAction(ia_rightTriggerTouch, ETriggerEvent::Triggered, this, &AVR_Player::RightTriggerInput_Touch);
		enhancedInputComponent->BindAction(ia_rightTriggerTouch, ETriggerEvent::Completed, this, &AVR_Player::RightTriggerInput_Touch);

		enhancedInputComponent->BindAction(ia_rightTriggerBool, ETriggerEvent::Triggered, this, &AVR_Player::RightTriggerInput_Bool);
		enhancedInputComponent->BindAction(ia_rightTriggerBool, ETriggerEvent::Completed, this, &AVR_Player::RightTriggerInput_Bool);
		/*enhancedInputComponent->BindAction(ia_rightTriggerFloat, ETriggerEvent::Triggered , this, &AVR_Player::RightTriggerInput_Float);
		enhancedInputComponent->BindAction(ia_rightTriggerFloat, ETriggerEvent::Completed, this, &AVR_Player::RightTriggerInput_Float);*/

		enhancedInputComponent->BindAction(ia_rightThumbStick, ETriggerEvent::Triggered , this, &AVR_Player::RightThumbstickInput);
		enhancedInputComponent->BindAction(ia_rightThumbStick, ETriggerEvent::Completed, this, &AVR_Player::RightThumbstickInput);
		

	}
}

void AVR_Player::RightTriggerInput_Bool(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
		rightLog->SetText(FText::FromString(FString("RightTrigger Pressed!")));
	}
	else
	{
		rightLog->SetText(FText::FromString(FString("RightTrigger Released!")));
	}

}

void AVR_Player::RightTriggerInput_Float(const FInputActionValue& value)
{
	rightLog->SetText(FText::FromString(FString::Printf(TEXT("RightTrigger : %.2f"),value.Get<float>())));
}

void AVR_Player::RightThumbstickInput(const FInputActionValue& value)
{
	FVector2D inputValue = value.Get<FVector2D>();
	rightLog->SetText(FText::FromString(FString::Printf(TEXT("X: %.2f\r\nY: %.2f"), inputValue.X, inputValue.Y )));
}

void AVR_Player::RightTriggerInput_Touch(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
		rightLog->SetText(FText::FromString(FString("RightTrigger Touched!")));
	}
	else 
	{
		rightLog->SetText(FText::FromString(FString("RightTrigger Untouched!")));
	}

}

