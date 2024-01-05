// Fill out your copyright notice in the Description page of Project Settings.


#include "HandleActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
AHandleActor::AHandleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50));
	boxComp->SetWorldScale3D(FVector(0.15f));
	boxComp->SetCollisionObjectType(ECC_GameTraceChannel4);
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECR_Ignore);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AHandleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHandleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

