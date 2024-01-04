// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCar.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
AMyCar::AMyCar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
		
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50));
	boxComp->SetWorldScale3D(FVector(2, 0.8f, 1.0f));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void AMyCar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyCar::RotateCar(float angle)
{
	SetActorRotation(GetActorRotation() + FRotator(0,angle,0));

}

