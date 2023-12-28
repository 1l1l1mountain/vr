// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "VRBodyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYVRPROJECT_API UVRBodyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings")
	FVector leftHandLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings")
	FRotator leftHandRotation;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings")
	FVector rightHandLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings")
	FRotator rightHandRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings")
	FVector headLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings")
	FRotator headRotation;

};
