// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpActor.generated.h"

UCLASS()
class MYVRPROJECT_API APickUpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpActor();

	UPROPERTY(EditAnywhere, Category= "MySettings|Component")
	class UBoxComponent* boxComp;
	UPROPERTY(EditAnywhere, Category = "MySettings|Component")
	class UStaticMeshComponent* meshComp;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Grabbed(class USkeletalMeshComponent* handMesh);
};
