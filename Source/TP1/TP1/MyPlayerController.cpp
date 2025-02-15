// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "MyGameState.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (!IsLocalController()) return;

	AMyGameState* GS = GetWorld()->GetGameState<AMyGameState>();
	if (GS)
	{
		GS->OnTimerUpdated.AddDynamic(this, &AMyPlayerController::UpdateTimerUI);
	}


		if (TimerWidgetClass)
		{
			TimerWidget = CreateWidget<UMyWidget>(this, TimerWidgetClass);
		}
		if (TimerWidget)
		{
			TimerWidget->AddToViewport();
		}
}

void AMyPlayerController::UpdateTimerUI(float TimeLeft)
{
	if (TimerWidget)
	{
		TimerWidget->StartTimer(TimeLeft);
	}
}