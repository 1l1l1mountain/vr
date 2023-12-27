// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
// Sets default values
APickUpActor::APickUpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComp);
	boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	boxComp->SetCollisionProfileName(FName("PickUpPreset"));
	boxComp->SetSimulatePhysics(true);
	boxComp->SetEnableGravity(true);
	boxComp->SetWorldScale3D(FVector(0.1f,0.1f,0.3f));
	boxComp->SetBoxExtent(FVector(50));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	meshComp->SetRelativeLocation(FVector(0,0,-50.0f));
}

// Called when the game starts or when spawned
void APickUpActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickUpActor::Grabbed(USkeletalMeshComponent* handMesh, EAttachmentRule attachmentRules)
{
	// 잡혔을 때의 핸드 메시에 부착된다.
	
	
	//!! 물리가 적용이 되면 적용이 안됨. 피직스를 오프 시켜야함. 물리가 적용되면, 오류남.
	boxComp->SetSimulatePhysics(false);
	// 잡는 순간의 간격을 (월드 좌표 기준) 유지하면서 붙인다.
	/*FAttachmentTransformRules attachmentRules = FAttachmentTransformRules::KeepWorldTransform;
	AttachToComponent(handMesh, attachmentRules);*/


	
	if (attachmentRules ==EAttachmentRule::KeepWorld)
	{
		FAttachmentTransformRules rules = FAttachmentTransformRules::KeepWorldTransform;
		//잡는 순간의 간격을 (월드 좌표 기준) 유지하면서 붙인다.
		AttachToComponent(handMesh, rules);
	}
	// 지정된 위치로 이동해서 붙인다.
	else if (attachmentRules == EAttachmentRule::SnapToTarget)
	{


		FAttachmentTransformRules rules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
		AttachToComponent(handMesh, rules, FName("GrabSocket"));
		SetActorRelativeLocation(locationOffset);
	
	}
	
}

void APickUpActor::Released(FVector deltaPosition, FQuat deltaRotation)
{
	//떼는건 붙이는 것의 역순
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	boxComp->SetSimulatePhysics(true);
	

	// 릴리즈될 당시의 속도와 각속도를 추가해준다.
	if (deltaPosition.Size() > 0.05f)
	{

		boxComp->AddImpulse(deltaPosition * throwPower );
		boxComp->AddTorqueInRadians(deltaRotation.GetRotationAxis() * rotPower);
	}

}

