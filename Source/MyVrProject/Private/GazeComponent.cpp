

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
	//���� ���ڵ�
	//FHitResult hitInfo;
	//FVector startLoc = player->hmdMesh->GetComponentLocation();
	//FVector dir = player->hmdMesh->GetForwardVector();
	//FVector endLoc = startLoc + dir * 500;
	////����, �ü� ���⿡ ��ü�� �ִٸ� ������ �������� ũ�⸦ ���� ��Ų��(MaxSize������).
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
	////�׷��� �ʴٸ� ������ �������� ũ�⸦ ���� ��Ų��(MinSize������).
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
	
	//or ���� ���
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
