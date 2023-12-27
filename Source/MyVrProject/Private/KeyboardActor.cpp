// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyboardActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
AKeyboardActor::AKeyboardActor()
{
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComp);
	boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	boxComp->SetCollisionObjectType(ECC_GameTraceChannel3);
	boxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel2,ECR_Overlap);
	boxComp->SetBoxExtent(FVector(50));
	boxComp->SetWorldScale3D(FVector(0.2f, 0.05f, 0.05f));


	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	meshComp->SetRelativeLocation(FVector(0, 0, -50));
	

}

void AKeyboardActor::BeginPlay()
{
	Super::BeginPlay();
	
	//Box Component  �� �浹 �̺�Ʈ �Լ� ���ε��ϱ�
	boxComp->OnComponentBeginOverlap.AddDynamic(this,&AKeyboardActor::OnHitKey);
	keyMat = UMaterialInstanceDynamic::Create(meshComp->GetMaterial(0), this);
	meshComp->SetMaterial(0, keyMat);
}

void AKeyboardActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKeyboardActor::OnHitKey(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(),keySound, GetActorLocation());
	keyMat->SetVectorParameterValue(FName("EmissiveColor"),FVector4((0.342402,  1.0, 0.169798, 1.0)));
	keyMat->SetScalarParameterValue(FName("Intensity"), 5.0f);

	//�����ð� �ִ� �Լ� ����
	FTimerHandle resetHandler;
	GetWorldTimerManager().ClearTimer(resetHandler);
	GetWorldTimerManager().SetTimer(resetHandler, this, &AKeyboardActor::ResetKeyColor, 0.5f, false);
	//�����ð� �ִ� �Լ� ����


}

void AKeyboardActor::ResetKeyColor()
{
	keyMat->SetVectorParameterValue(FName("EmissiveColor"), FVector4((1.0, 1.0, 1.0, 1.0)));
	keyMat->SetScalarParameterValue(FName("Intensity"), 1.0f);


}

