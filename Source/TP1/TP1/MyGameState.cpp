// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameState.h"

#include "MyWidget.h"
#include "Net/UnrealNetwork.h"

AMyGameState::AMyGameState()
{
}

void AMyGameState::OnRep_TimerEnd()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
			FString::Printf(TEXT("On Rep")));
	float TimeLeft = TimerEnd - GetServerWorldTimeSeconds();
	TimeLeft = FMath::Max(TimeLeft, 0.0f);

	OnTimerUpdated.Broadcast(TimeLeft);
}

void AMyGameState::ServerBroadcastTimerEnd_Implementation()
{
	OnTimerEnd.Broadcast();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Broadcast end (server)"));
	
}

void AMyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyGameState, TimerEnd);
	DOREPLIFETIME(AMyGameState, bTimerStarted);
}
