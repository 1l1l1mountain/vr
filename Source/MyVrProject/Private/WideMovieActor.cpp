// Fill out your copyright notice in the Description page of Project Settings.


#include "WideMovieActor.h"
#include "Components/SceneComponent.h"
#include "Components/WidgetComponent.h"
#include "MediaPlayer.h"
#include "MovieWidget.h"
// Sets default values
AWideMovieActor::AWideMovieActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(rootComp);

	movieWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Component"));
	movieWidget->SetupAttachment(rootComp);

	
}

// Called when the game starts or when spawned
void AWideMovieActor::BeginPlay()
{
	Super::BeginPlay();
	if (moviePlayer != nullptr)
	{
		//�̵�� �ҽ��� �̵�� �÷��̾ �ִ´�.
		moviePlayer->OpenSource(movieSource);
	}


	//������ �ڽ��� �����ͷ� ����Ű���� ���ش�. (���� ����)
	Cast<UMovieWidget>(movieWidget->GetWidget())->movieActor = this;


	//���콺 Ŀ�� ǥ���ϱ�
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

}

// Called every frame
void AWideMovieActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWideMovieActor::Back()
{
	if (moviePlayer->IsPlaying() || moviePlayer->IsPaused())
	{
		if (moviePlayer->GetTime().GetTotalSeconds() > 10)
		{

		FTimespan newTime = moviePlayer->GetTime() - FTimespan(0, 0, 10);
		moviePlayer->Seek(newTime);

		}
		else
		{
			moviePlayer->Seek(FTimespan(0,0,0));
		}
	}

}

void AWideMovieActor::Stop()
{
	if (moviePlayer->IsPlaying())
	{

		moviePlayer->Close();
	}

}

void AWideMovieActor::Play()
{

	if (moviePlayer->IsClosed())
	{
		moviePlayer->OpenSource(movieSource); //Ŭ����� �������� ������ ������ �����������.
	}
	else if (moviePlayer->IsPlaying())
	{
		moviePlayer->Pause();
	}
	else if (moviePlayer->IsPaused())
	{
		moviePlayer->Play(); //�������� ������ �ʾұ� ������ �׳� �÷��̰���
	}
}

void AWideMovieActor::Forward()
{
	if (moviePlayer->IsPlaying() || moviePlayer->IsPaused())
	{
		FTimespan newTime = moviePlayer->GetTime() + FTimespan(0, 0, 10);
		moviePlayer->Seek(newTime);
	}
}

