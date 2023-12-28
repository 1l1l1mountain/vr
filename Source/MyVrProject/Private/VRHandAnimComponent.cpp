#include "VRHandAnimComponent.h"
#include "EnhancedInputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "VRHandAnimInstance.h"
#include "VR_Player.h"
UVRHandAnimComponent::UVRHandAnimComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UVRHandAnimComponent::BeginPlay()
{
	Super::BeginPlay();

	player = GetOwner<AVR_Player>();
	if (player != nullptr) 
	{

		handAnim_Left = Cast<UVRHandAnimInstance>(player->leftHand->GetAnimInstance());
		if(handAnim_Left)
		{
			handAnim_Left->bMirror_cpp = true;
		
		}
		handAnim_Right = Cast<UVRHandAnimInstance>(player->rightHand->GetAnimInstance());
		if (handAnim_Right)
		{
			handAnim_Right->bMirror_cpp = false;

		}

	}
}


void UVRHandAnimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UVRHandAnimComponent::SetupPlayerInputComponent(UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*> inputs)
{

	enhancedInputComponent->BindAction(inputs[5],ETriggerEvent::Triggered, this, &UVRHandAnimComponent::InputIndexTriggerValue_Left);

	enhancedInputComponent->BindAction(inputs[5], ETriggerEvent::Completed, this, &UVRHandAnimComponent::InputIndexTriggerValue_Left);


	enhancedInputComponent->BindAction(inputs[6], ETriggerEvent::Triggered, this, &UVRHandAnimComponent::InputGripValue_Left);

	enhancedInputComponent->BindAction(inputs[6], ETriggerEvent::Completed, this, &UVRHandAnimComponent::InputGripValue_Left);

	enhancedInputComponent->BindAction(inputs[7], ETriggerEvent::Triggered, this, &UVRHandAnimComponent::InputIndexTriggerTouch_Left);

	enhancedInputComponent->BindAction(inputs[7], ETriggerEvent::Completed, this, &UVRHandAnimComponent::InputIndexTriggerTouch_Left);

	enhancedInputComponent->BindAction(inputs[8], ETriggerEvent::Triggered, this, &UVRHandAnimComponent::InputThumbstickTouch_Left);
	enhancedInputComponent->BindAction(inputs[8], ETriggerEvent::Completed, this, &UVRHandAnimComponent::InputThumbstickTouch_Left);

	enhancedInputComponent->BindAction(inputs[9], ETriggerEvent::Triggered, this, &UVRHandAnimComponent::InputIndexTriggerValue_Right);
	enhancedInputComponent->BindAction(inputs[9], ETriggerEvent::Completed, this, &UVRHandAnimComponent::InputIndexTriggerValue_Right);

	enhancedInputComponent->BindAction(inputs[10], ETriggerEvent::Triggered, this, &UVRHandAnimComponent::InputGripValue_Right);
	enhancedInputComponent->BindAction(inputs[10], ETriggerEvent::Completed, this, &UVRHandAnimComponent::InputGripValue_Right);

	enhancedInputComponent->BindAction(inputs[11], ETriggerEvent::Triggered, this, &UVRHandAnimComponent::InputIndexTriggerTouch_Right);
	enhancedInputComponent->BindAction(inputs[11], ETriggerEvent::Completed, this, &UVRHandAnimComponent::InputIndexTriggerTouch_Right);

	enhancedInputComponent->BindAction(inputs[12], ETriggerEvent::Triggered, this, &UVRHandAnimComponent::InputThumbstickTouch_Right);
	enhancedInputComponent->BindAction(inputs[12], ETriggerEvent::Completed, this, &UVRHandAnimComponent::InputThumbstickTouch_Right);


}

void UVRHandAnimComponent::InputIndexTriggerValue_Left(const FInputActionValue& value)
{
	if (handAnim_Left != nullptr)
	{
		handAnim_Left->PoseAlphaIndexCurl_cpp = value.Get<float>();

	}
}

void UVRHandAnimComponent::InputGripValue_Left(const FInputActionValue& value)
{

	if (handAnim_Left != nullptr)
	{
		handAnim_Left->PoseAlphaGrasp_cpp = value.Get<float>();

	}

}

void UVRHandAnimComponent::InputIndexTriggerTouch_Left(const FInputActionValue& value)
{
	if (handAnim_Left != nullptr)
	{
		handAnim_Left->PoseAlphaPoint_cpp = value.Get<bool>();

	}

}

void UVRHandAnimComponent::InputThumbstickTouch_Left(const FInputActionValue& value)
{

	if (handAnim_Left != nullptr)
	{
		handAnim_Left->PoseAlphaThumbUp_cpp = value.Get<bool>();

	}
}

void UVRHandAnimComponent::InputIndexTriggerValue_Right(const FInputActionValue& value)
{
	if (handAnim_Right != nullptr)
	{
		handAnim_Right->PoseAlphaIndexCurl_cpp = value.Get<float>();

	}
}

void UVRHandAnimComponent::InputGripValue_Right(const FInputActionValue& value)
{
	if (handAnim_Right != nullptr)
	{
		handAnim_Right->PoseAlphaGrasp_cpp = value.Get<float>();

	}
}

void UVRHandAnimComponent::InputIndexTriggerTouch_Right(const FInputActionValue& value)
{
	if (handAnim_Right != nullptr)
	{
		handAnim_Right->PoseAlphaPoint_cpp = value.Get<bool>();

	}
}

void UVRHandAnimComponent::InputThumbstickTouch_Right(const FInputActionValue& value)
{
	if (handAnim_Right != nullptr)
	{
		handAnim_Right->PoseAlphaThumbUp_cpp = value.Get<bool>();

	}
}

