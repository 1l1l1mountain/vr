// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "VR_Player.generated.h"

UCLASS()
class MYVRPROJECT_API AVR_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVR_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Components")
	class UCameraComponent* cameraComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Components")
	class UStaticMeshComponent* hmdMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Components")
	class UMotionControllerComponent* leftController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Components")
	class USkeletalMeshComponent* leftHand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Components")
	class UWidgetInteractionComponent* leftPointer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Components")
	class UMotionControllerComponent* rightController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Components")
	class USkeletalMeshComponent* rightHand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Components")
	class UWidgetInteractionComponent* rightPointer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Components")
	class UTextRenderComponent* leftLog;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Components")
	class UTextRenderComponent* rightLog;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Components")
	class UMoveComponent* moveComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Components")
	class UNiagaraComponent* teleportFX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Components")
	class UGrabComponent* grabComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Components")
	class UVRHandAnimComponent* handAnimComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Components")
	class UStaticMeshComponent* gazeMeshComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Components")
	class UGazeComponent* gazeComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Components")
	class UWidgetPointerComponent* widgetPointerComp;


	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Inputs")
	class UInputMappingContext* imc;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Inputs")
	//class UInputAction* ia_rightTriggerBool;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Inputs")
	//class UInputAction* ia_rightTriggerFloat;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Inputs")
	//class UInputAction* ia_rightThumbStick;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Inputs")
	//class UInputAction* ia_rightTriggerTouch;

	////3일차
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Inputs")
	//class UInputAction* ia_moveInput;
	//float speed;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Inputs")
	//class UInputAction* ia_mouseInput;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Inputs")
	//class UInputAction* ia_leftTriggerBool;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Inputs")
	TArray<class UInputAction*> ia_inputs;

private:
	void RightTriggerInput_Bool(const FInputActionValue& value); //외부에서 받는 값을 바꾸지 않겠다.
	void RightTriggerInput_Float(const FInputActionValue& value);
	void RightThumbstickInput(const FInputActionValue& value);
	void RightTriggerInput_Touch(const FInputActionValue& value);


	//3일차
	void PlayerMove(const FInputActionValue& value);
	void PlayerRotate(const FInputActionValue& value);
	void BasicTeleport(float sightRange, FVector direction,FVector pivot);


	class UVRBodyAnimInstance* bodyAnim;
};
