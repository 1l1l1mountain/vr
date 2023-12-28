// Fill out your copyright notice in the Description page of Project Settings.


#include "VRHandAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"

void UVRHandAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	//부모의 내용이 있다면 먼저 실행
	Super::NativeUpdateAnimation(DeltaSeconds);

	//1. FMath 클래스 함수를 이용할 때
	//CurrentPoseAlpha 변수의 값을 PoseAlpha 변수의 값이 되도록 서서히(1초) 변경한다.
	CurrentPoseAlphaPoint_cpp = FMath::Lerp(CurrentPoseAlphaPoint_cpp, PoseAlphaPoint_cpp, DeltaSeconds* 13.0f);
	CurrentPoseAlphaThumbUp_cpp = FMath::Lerp(CurrentPoseAlphaThumbUp_cpp,PoseAlphaThumbUp_cpp, DeltaSeconds* 13.0f);

	//2. KismetMathLibrary 클래스 함수를 이용할 때
	UKismetMathLibrary::FInterpTo(CurrentPoseAlphaPoint_cpp,PoseAlphaPoint_cpp, DeltaSeconds, 13);
	UKismetMathLibrary::FInterpTo(CurrentPoseAlphaThumbUp_cpp, PoseAlphaThumbUp_cpp, DeltaSeconds, 13);

}
