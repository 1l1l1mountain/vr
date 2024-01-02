// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MovieWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYVRPROJECT_API UMovieWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, Category = "MySettings", meta=(BindWidget))
	class UImage* screen;

	UPROPERTY(EditAnywhere, Category = "MySettings", meta = (BindWidget))
	class UButton* btn_back;

	UPROPERTY(EditAnywhere, Category = "MySettings", meta = (BindWidget))
	class UButton* btn_stop;

	UPROPERTY(EditAnywhere, Category = "MySettings", meta = (BindWidget))
	class UButton* btn_play;
	
	UPROPERTY(EditAnywhere, Category = "MySettings", meta = (BindWidget))
	class UButton* btn_forward;
	
	class AWideMovieActor* movieActor;

private:
	UFUNCTION()
	void Back10seconds();
	UFUNCTION()
	void StopMovie();
	UFUNCTION()
	void PlayMovie();
	UFUNCTION()
	void Forward10Seconds();

};
