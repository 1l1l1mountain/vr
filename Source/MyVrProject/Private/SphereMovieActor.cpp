// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereMovieActor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MediaPlayer.h"
#include "MediaSource.h"
#include "MediaSoundComponent.h"
// Sets default values
ASphereMovieActor::ASphereMovieActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(rootComp);
	rootComp->SetWorldScale3D(FVector(3.0f));


	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh Comp"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	soundComp = CreateDefaultSubobject<UMediaSoundComponent>(TEXT("Sound Comp"));
	soundComp->SetupAttachment(RootComponent);

	if (mediaPlayer != nullptr)
	{
		soundComp->SetMediaPlayer(mediaPlayer);
	}
}

// Called when the game starts or when spawned
void ASphereMovieActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (mediaPlayer != nullptr && mediaSource != nullptr)
	{
		mediaPlayer->OpenSource(mediaSource);
		//soundComp->Activate(true);
		//soundComp->SetVolumeMultiplier(0); //음량 조절

	}

} 

// Called every frame
void ASphereMovieActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

