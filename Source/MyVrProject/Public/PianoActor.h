// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PianoActor.generated.h"

UCLASS()
class MYVRPROJECT_API APianoActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APianoActor();

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	TArray<class USoundBase*> keySounds;
	
	UPROPERTY(EditAnywhere, Category = "MySettings")
	TArray<class UChildActorComponent *> keyActors;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
