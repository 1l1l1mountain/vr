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
	// ������ ���� �ڵ� �޽ÿ� �����ȴ�.
	
	
	//!! ������ ������ �Ǹ� ������ �ȵ�. �������� ���� ���Ѿ���. ������ ����Ǹ�, ������.
	boxComp->SetSimulatePhysics(false);
	// ��� ������ ������ (���� ��ǥ ����) �����ϸ鼭 ���δ�.
	/*FAttachmentTransformRules attachmentRules = FAttachmentTransformRules::KeepWorldTransform;
	AttachToComponent(handMesh, attachmentRules);*/


	
	if (attachmentRules ==EAttachmentRule::KeepWorld)
	{
		FAttachmentTransformRules rules = FAttachmentTransformRules::KeepWorldTransform;
		//��� ������ ������ (���� ��ǥ ����) �����ϸ鼭 ���δ�.
		AttachToComponent(handMesh, rules);
	}
	// ������ ��ġ�� �̵��ؼ� ���δ�.
	else if (attachmentRules == EAttachmentRule::SnapToTarget)
	{


		FAttachmentTransformRules rules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
		AttachToComponent(handMesh, rules, FName("GrabSocket"));
		SetActorRelativeLocation(locationOffset);
	
	}
	
}

void APickUpActor::Released(FVector deltaPosition, FQuat deltaRotation)
{
	//���°� ���̴� ���� ����
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	boxComp->SetSimulatePhysics(true);
	

	// ������� ����� �ӵ��� ���ӵ��� �߰����ش�.
	if (deltaPosition.Size() > 0.05f)
	{

		boxComp->AddImpulse(deltaPosition * throwPower );
		boxComp->AddTorqueInRadians(deltaRotation.GetRotationAxis() * rotPower);
	}

}

