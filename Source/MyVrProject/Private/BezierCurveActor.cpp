// Fill out your copyright notice in the Description page of Project Settings.


#include "BezierCurveActor.h"

// Sets default values
ABezierCurveActor::ABezierCurveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	p0 = CreateDefaultSubobject<USceneComponent>(TEXT("P0"));
	p0->SetupAttachment(RootComponent);

	p1 = CreateDefaultSubobject<USceneComponent>(TEXT("P1"));
	p1->SetupAttachment(RootComponent);

	p2 = CreateDefaultSubobject<USceneComponent>(TEXT("P2"));
	p2->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABezierCurveActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABezierCurveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawBezierCurve(p0->GetComponentLocation(), p1->GetComponentLocation(), p2->GetComponentLocation());
}

void ABezierCurveActor::DrawBezierCurve(FVector loc0, FVector loc1, FVector loc2)
{

	TArray<FVector> linePositions;
	FVector m0;
	FVector m1;
	FVector b;
	
	//계산
	for (float i = 0;i < 1.0f / 20;i = i + 0.05)
	{
		FVector m0 = FMath::Lerp(loc0, loc1, i);
		FVector m1 = FMath::Lerp(loc1, loc2, i);
		FVector b = FMath::Lerp(m0, m1, i);
	
		linePositions.Add(b);
	}

	//그리기
	UWorld* world = GetWorld();
	DrawDebugLine(world, loc0, loc1, FColor::Black, false, 0, 0, 2);
	DrawDebugLine(world, loc1, loc2, FColor::Black, false, 0, 0, 2);
	DrawDebugPoint(world,m0,10,FColor::White, false , 0 ,0 );
	DrawDebugPoint(world,m1,10,FColor::White, false , 0 ,0 );
	DrawDebugPoint(world,b,10,FColor::Purple, false , 0 ,0 );

	if (linePositions.Num() > 0)
	{
		for (int32 i = 0;i < linePositions.Num() - 1;i++)
		{

			DrawDebugLine(world, linePositions[i], linePositions[i + 1], FColor::Magenta, false, 0, 0, 1);
		}

	}


}

