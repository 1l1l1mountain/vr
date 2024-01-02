// Fill out your copyright notice in the Description page of Project Settings.


#include "MovieWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "WideMovieActor.h"

void UMovieWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//버튼을 클릭하는 이벤트에 함수를 연결한다.
	btn_back->OnClicked.AddDynamic(this, &UMovieWidget::Back10seconds);
	btn_stop->OnClicked.AddDynamic(this, &UMovieWidget::StopMovie);
	btn_play->OnClicked.AddDynamic(this, &UMovieWidget::PlayMovie);
	btn_forward->OnClicked.AddDynamic(this,&UMovieWidget::Forward10Seconds);
}

void UMovieWidget::Back10seconds()
{
	if (movieActor != nullptr)
	{
		movieActor->Back();
	}

}

void UMovieWidget::StopMovie()
{
	if (movieActor != nullptr)
	{
		movieActor->Stop();
	}

}

void UMovieWidget::PlayMovie()
{

	if (movieActor != nullptr)
	{
		movieActor->Play();
	}

}

void UMovieWidget::Forward10Seconds()
{
	if (movieActor != nullptr)
	{
		movieActor->Forward();
	}

}
