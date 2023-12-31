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
#include "Components/CapsuleComponent.h"
#include "MoveComponent.h"
#include "NiagaraComponent.h"
#include "GrabComponent.h"
#include "VRHandAnimComponent.h"
#include "VRBodyAnimInstance.h"
#include "GazeComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include "WidgetPointerComponent.h"
#include "MyCar.h"
#include "EngineUtils.h"
#include "CarControllerComponent.h"
#include "ClimbComponent.h"
// Sets default values
AVR_Player::AVR_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cameraComp->SetupAttachment(RootComponent);

	gazeMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gaze Mesh"));
	gazeMeshComp->SetupAttachment(cameraComp);
	gazeMeshComp->SetRelativeLocationAndRotation(FVector(100,0,0), FRotator(0,-90,-90));
	gazeMeshComp->SetWorldScale3D(FVector(0.1f));

	hmdMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HMD Mesh"));
	hmdMesh->SetupAttachment(cameraComp);

	leftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Left Controller"));
	leftController->SetupAttachment(RootComponent);
	leftController->SetRelativeLocation(FVector(50,-30,-10));
	leftController->SetTrackingMotionSource(FName("Left")); // 실제 트래커가 가진 컨트롤러의 값을 읽겠다느낌

	leftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Hand Mesh"));
	leftHand->SetupAttachment(leftController);
	leftHand->SetRelativeRotation(FRotator(-70,-180,90));
	//(Pitch=-70.000000,Yaw=-180.000000,Roll=90.000000)

	leftLog = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Left Log"));
	leftLog->SetupAttachment(leftHand);
	leftLog->SetRelativeLocation(FVector(-20, 10, 0));
	leftLog->SetRelativeRotation(FRotator(0,-90, -90));
	leftLog->SetHorizontalAlignment(EHTA_Center);
	leftLog->SetVerticalAlignment(EVRTA_TextCenter);
	leftLog->SetWorldSize(20);
	leftLog->SetTextRenderColor(FColor(255,255,0));

	leftPointer = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Left Widget Pointer"));
	leftPointer->SetupAttachment(leftHand);

	rightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right Controller"));
	rightController->SetupAttachment(RootComponent);
	rightController->SetRelativeLocation(FVector(50, 30, -10));
	rightController->SetTrackingMotionSource(FName("Right"));

	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand Mesh"));
	rightHand->SetupAttachment(rightController);
	rightHand->SetRelativeRotation(FRotator(70, 0,90));
	//(Pitch = 70.000000, Yaw = -0.000000, Roll = 90.000000)

	rightLog = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Right Log"));
	rightLog->SetupAttachment(rightHand);
	rightLog->SetRelativeLocation(FVector(20, 10, 0));
	rightLog->SetRelativeRotation(FRotator(0, -90, 90));
	rightLog->SetHorizontalAlignment(EHTA_Center);
	rightLog->SetVerticalAlignment(EVRTA_TextCenter);
	rightLog->SetWorldSize(20);
	rightLog->SetTextRenderColor(FColor(255, 255, 0));

	rightPointer = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Right Widget Pointer"));
	rightPointer->SetupAttachment(rightHand);

	teleportFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Teleport Effect"));
	teleportFX->SetupAttachment(leftHand);



	//액터 컴포넌트
	moveComp = CreateDefaultSubobject<UMoveComponent>(TEXT("Movce Component"));
	grabComp = CreateDefaultSubobject<UGrabComponent>(TEXT("Grab Component"));
	handAnimComp = CreateDefaultSubobject<UVRHandAnimComponent>(TEXT("VR Hand Anim Copmonent"));
	gazeComp = CreateDefaultSubobject<UGazeComponent>(TEXT("Gaze Copmonent"));
	widgetPointerComp = CreateDefaultSubobject<UWidgetPointerComponent>(TEXT("Widget Pointer Component"));
	carControllerComp = CreateDefaultSubobject<UCarControllerComponent>(TEXT("Car Controller Component"));
	climbComp = CreateDefaultSubobject<UClimbComponent>(TEXT("Climb Component"));
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
	bodyAnim = Cast<UVRBodyAnimInstance>(GetMesh()->GetAnimInstance());

	//월드에 차 액터를 찾아서 변수에 할당한다.
	for (TActorIterator<AMyCar> car(GetWorld()); car; ++car)
	{
		controlledCar = *car;
	}

}

// Called every frame
void AVR_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bodyAnim != nullptr)
	{
		bodyAnim->leftHandLocation = leftController->GetComponentLocation();
		bodyAnim->leftHandRotation = leftController->GetComponentRotation();

		bodyAnim->rightHandLocation = rightController->GetComponentLocation();
		bodyAnim->rightHandRotation = rightController->GetComponentRotation();

		bodyAnim->headLocation = cameraComp->GetComponentLocation();
		bodyAnim->headRotation = cameraComp->GetComponentRotation();



	}

	//일단 난 안됐음.. 
	/*if (controlledCar != nullptr)
	{
		controlledCar->RotateCar(0.1f);
	}*/

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
		/*enhancedInputComponent->BindAction(ia_rightTriggerTouch, ETriggerEvent::Triggered, this, &AVR_Player::RightTriggerInput_Touch);
		enhancedInputComponent->BindAction(ia_rightTriggerTouch, ETriggerEvent::Completed, this, &AVR_Player::RightTriggerInput_Touch);

		enhancedInputComponent->BindAction(ia_rightTriggerBool, ETriggerEvent::Triggered, this, &AVR_Player::RightTriggerInput_Bool);
		enhancedInputComponent->BindAction(ia_rightTriggerBool, ETriggerEvent::Completed, this, &AVR_Player::RightTriggerInput_Bool);*/



		//enhancedInputComponent->BindAction(ia_inputs[3], ETriggerEvent::Triggered, this, &AVR_Player::RightTriggerInput_Float);
		//enhancedInputComponent->BindAction(ia_inputs[3], ETriggerEvent::Completed, this, &AVR_Player::RightTriggerInput_Float);

		//enhancedInputComponent->BindAction(ia_rightThumbStick, ETriggerEvent::Triggered , this, &AVR_Player::RightThumbstickInput);
		//enhancedInputComponent->BindAction(ia_rightThumbStick, ETriggerEvent::Completed, this, &AVR_Player::RightThumbstickInput);
		//
		////3일차 
		enhancedInputComponent->BindAction(ia_inputs[1], ETriggerEvent::Triggered, this, &AVR_Player::PlayerMove); //인핸스 인풋은 무조건 바인드액션으로
		enhancedInputComponent->BindAction(ia_inputs[2], ETriggerEvent::Triggered, this, &AVR_Player::PlayerRotate);


		//컴포넌트에 입력 이벤트 넘겨주기
		moveComp->SetupPlayerInputComponent(enhancedInputComponent, ia_inputs);
		grabComp->SetupPlayerInputComponent(enhancedInputComponent, ia_inputs);
		handAnimComp->SetupPlayerInputComponent(enhancedInputComponent, ia_inputs);
		widgetPointerComp->SetupPlayerInputComponent(enhancedInputComponent, ia_inputs);
		carControllerComp->SetupPlayerInputComponent(enhancedInputComponent, ia_inputs);
		climbComp->SetupPlayerInputComponent(enhancedInputComponent, ia_inputs);
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
	//UE_LOG(LogTemp, Log, TEXT("X : %.2f"),value.Get<float>());
	BasicTeleport(500, rightController->GetForwardVector(), rightController->GetComponentLocation());

}

void AVR_Player::RightThumbstickInput(const FInputActionValue& value)
{
	FVector2D inputValue = value.Get<FVector2D>();
	rightLog->SetText(FText::FromString(FString::Printf(TEXT("X: %.2f\r\nY: %.2f"), inputValue.X, inputValue.Y )));
	
	AddControllerYawInput(inputValue.X);
	//회전 add controller yaw input
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

void AVR_Player::PlayerMove(const FInputActionValue& value)
{


	//FVector2D inputValue = value.Get<FVector2D>();
	//leftLog->SetText(FText::FromString(FString::Printf(TEXT("X: %.2f\r\nY: %.2f"), inputValue.X, inputValue.Y)));
	////inputValue.X  
	////inputValue.Y
	//
	////P= P0 + VT
	//
	//FVector P0 = GetActorLocation();
	//FVector dir = FVector(inputValue.X, 0, 0) + FVector(0, inputValue.Y, 0);
	//dir.Normalize();
	//
	//FVector velocity = speed * dir;
	//SetActorLocation(P0 + velocity * GetWorld()->GetDeltaSeconds());
	
	// ----- 강의
	// 1. 플레이어가 입력(상w하s좌a우d + 썸스틱)한대로 
	FVector inputDir = FVector(value.Get<FVector2D>().X, value.Get<FVector2D>().Y, 0);//밸류값 변환 구조체에서 쓰고 싶은 형태로(IA에서 정한 형태로)
	
	//UE_LOG(LogTemp, Log, TEXT("X: %.2f, Y: %.2f, Z: %.2f"), inputDir.X, inputDir.Y, inputDir.Z);
	
	//트랜스폼 디렉션 써도 되지만, 두벡터를 내적해서 구해도 됨.
	
	
	// 2. 기준 회전 형태에서의 방향을 현재 회전된 방향에 맞춰 변환한다. 
	FVector modifiedDir = GetTransform().TransformVector(inputDir);
	//퀀터니엄 : 퀀터니엄과 벡터를 곱한만큼, ??? 퀀터니엄 수식 외우기.

	// 3. 이동한다.
	AddMovementInput(modifiedDir);

}

void AVR_Player::PlayerRotate(const FInputActionValue& value)
{
	//float inputValue = value.Get<float>();
	//AddControllerYawInput(inputValue);

	//--- 강의
	
	// 입력(좌우 : mouse 가로 방향)대로 
	float inputDir = value.Get<float>();

	// 회전한다.
	AddControllerYawInput(inputDir);
	//AddControllerPitchInput(inputDir);


}

void AVR_Player::BasicTeleport(float sightRange, FVector direction, FVector pivot)
{
	//가리킨 지점(direction 방향으로 SightRange 거리만큼 발사한 라인이 땅과 닿은 지점)으로 
	FHitResult hitInfo;
	FVector startVec = pivot;
	FVector endVec = startVec + direction * sightRange; 
	bool bIsCollide = GetWorld()->LineTraceSingleByChannel(hitInfo,startVec, endVec,ECC_Visibility);


	// 만일, 닿았다면 나를 이동시킨다.
	if (bIsCollide)
	{
		SetActorLocation(hitInfo.ImpactPoint + FVector(0,0,GetCapsuleComponent()->GetScaledCapsuleHalfHeight())); //분배효과 조심
			
		// 닿았다면 닿은 지점까지 라인을 그린다.
		DrawDebugLine(GetWorld(),startVec,hitInfo.ImpactPoint,FColor::Red);
	}
	// 닿지 않았다면 최대 지점까지 그린다.
	else
	{
		DrawDebugLine(GetWorld(), startVec, endVec, FColor::Green);

	
	}

	


}

