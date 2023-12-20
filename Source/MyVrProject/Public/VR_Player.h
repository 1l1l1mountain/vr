// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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
	class UMotionControllerComponent* rightController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Components")
	class USkeletalMeshComponent* rightHand;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Components")
	class UTextRenderComponent* leftLog;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Components")
	class UTextRenderComponent* rightLog;

};
