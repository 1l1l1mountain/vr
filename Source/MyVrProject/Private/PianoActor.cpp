// Fill out your copyright notice in the Description page of Project Settings.


#include "PianoActor.h"
#include "Components/SceneComponent.h"
#include "Components/ChildActorComponent.h"
#include "KeyboardActor.h"
// Sets default values
APianoActor::APianoActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(rootComp);
	
	float width = (5 * 8) + (3 * (8 - 1));
	FVector startLoc = FVector(0, width * 0.5f * -1 + 2.5f, 0);

	for (int32 i = 0;i < 8;i++)
	{
		FString actorName = FString::Printf(TEXT("Keyboard_%d"), i +1 );
		//���͸� ������Ʈó��
		UChildActorComponent* children = CreateDefaultSubobject<UChildActorComponent>(FName(*actorName));
		children->SetupAttachment(RootComponent);
		keyActors.Add(children);
		
		

		
		children->SetRelativeLocation(startLoc + FVector (0, 8 * i , 0));

	}
}

// Called when the game starts or when spawned
void APianoActor::BeginPlay()
{
	Super::BeginPlay();
	

	for(int32 i=0 ;i < keySounds.Num();i++)
	{
	
	
	//������ Ű���� ���͵鸶�� ������ �ִ� keySound ������ ���� ���ϵ��� �־��ش�.
	if (keyActors[i]->GetChildActor() != nullptr)
	{

		Cast<AKeyboardActor>(keyActors[i]->GetChildActor())->keySound = keySounds[i];
	}

	
	}
}

// Called every frame
void APianoActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

