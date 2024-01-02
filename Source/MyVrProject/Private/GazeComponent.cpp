

#include "GazeComponent.h"
#include "VR_Player.h"
#include "Camera/CameraComponent.h"
UGazeComponent::UGazeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UGazeComponent::BeginPlay()
{
	Super::BeginPlay();

	player = GetOwner<AVR_Player>();

	baseSize = player->gazeMeshComp->GetComponentScale();
	
}


void UGazeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//내가 쓴코드
	//FHitResult hitInfo;
	//FVector startLoc = player->hmdMesh->GetComponentLocation();
	//FVector dir = player->hmdMesh->GetForwardVector();
	//FVector endLoc = startLoc + dir * 500;
	////만일, 시선 방향에 물체가 있다면 게이즈 포인터의 크기를 증가 시킨다(MaxSize까지만).
	//
	//if (GetWorld()->LineTraceSingleByChannel(hitInfo, startLoc, endLoc, ECC_Visibility))
	//{
	//	if(i<= 1)
	//	{ 
	//	i += 0.05;
	//	FVector  x = FMath::Lerp(minSize, maxSize, FVector(i));
	//	player->gazeMeshComp->SetWorldScale3D(x);
	//	UE_LOG(LogTemp, Warning, TEXT("Up%f"), i);
	//
	//	}
	//}
	////그렇지 않다면 게이즈 포인터의 크기를 감소 시킨다(MinSize까지만).
	//else
	//{
	//	if (i >=0)
	//	{
	//		i -= 0.05;
	//		FVector  x = FMath::Lerp(minSize, maxSize, FVector(i));
	//		player->gazeMeshComp->SetWorldScale3D(x);
	//		UE_LOG(LogTemp, Warning, TEXT("Down%f"), i);

	//	}

	//}


	if (GazeCheck())
	{

		currentSize += DeltaTime;
	}
	else
	{
		currentSize -= DeltaTime;
	}

	//currentSize = FMath::Clamp(currentSize, 0.1f,1.0f);
	//player->gazeMeshComp->SetWorldScale3D(baseSize * currentSize);
	
	//or 러프 방식
	currentSize = FMath::Clamp(currentSize, 0.1f,1.0f);
	FVector newSize = FMath::Lerp(minSize, maxSize, currentSize);
	player->gazeMeshComp->SetWorldScale3D(baseSize.X * newSize);


}

bool UGazeComponent::GazeCheck()
{
	FHitResult hitInfo;
	FVector startVec = player->cameraComp->GetComponentLocation();
	FVector endVec = startVec + player->cameraComp->GetForwardVector()* 1000.0f;
	FCollisionQueryParams params;
	params.AddIgnoredActor(player);
		
	return  GetWorld()->LineTraceSingleByChannel(hitInfo, startVec, endVec, ECC_Visibility, params);


}
