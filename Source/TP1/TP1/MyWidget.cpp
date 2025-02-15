// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWidget.h"

#include "MyGameState.h"
#include "Components/TextBlock.h"
#include "TP1/GameMode/GameModeLobby.h"

void UMyWidget::StartTimer(float TimeLeft)
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMyWidget::UpdateTimer, 0.2f, true);
	CurrentTimeLeft = TimeLeft;
}

void UMyWidget::UpdateTimer()
{
	CurrentTimeLeft -= 0.2f;
	if (CurrentTimeLeft <= 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		AMyGameState* GS = GetWorld()->GetGameState<AMyGameState>();
		if (GS)
		{
			//GS->ServerBroadcastTimerEnd();
			if (AGameModeLobby* GM = Cast<AGameModeLobby>(GetWorld()->GetAuthGameMode()))
			{
				GM->StartGame();
			}
		}
	}

	FText TimerText = FText::FromString(FString::Printf(TEXT("%.1f"), CurrentTimeLeft));
	TimerTextBlock->SetText(TimerText);
}
