// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeLobby.h"

#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "TP1/TP1/MyGameState.h"
#include "TP1/TP1/MyPlayerState.h"

AGameModeLobby::AGameModeLobby()
{
	bUseSeamlessTravel = true;
}

void AGameModeLobby::BeginPlay()
{
	Super::BeginPlay();

	AMyGameState* GS = GetWorld()->GetGameState<AMyGameState>();
	if (GS)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
				FString::Printf(TEXT("Added Dynamic")));
		GS->OnTimerEnd.AddDynamic(this, &AGameModeLobby::StartGame);
	}
}

void AGameModeLobby::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GameState->PlayerArray.Num() >= 2)
	{
		AMyGameState* GS = GetWorld()->GetGameState<AMyGameState>();
		if (GS && !GS->bTimerStarted)
			{
			GS->bTimerStarted = true;
			StartCountdownTimer();
        
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
				FString::Printf(TEXT("Started Timer")));
			}
	}
}


FString AGameModeLobby::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
	const FString& Options, const FString& Portal)
{

	FString SkinIndexOption = UGameplayStatics::ParseOption(Options, TEXT("SkinIndex"));
	if (!SkinIndexOption.IsEmpty())
	{
		DefaultSelectedSkinIndex = FCString::Atoi(*SkinIndexOption);
		NewPlayerController->GetPlayerState<AMyPlayerState>()->SetSkinIndex(DefaultSelectedSkinIndex);
	}
	return Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
}

void AGameModeLobby::StartGame()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
				FString::Printf(TEXT("Server Travel")));
	GetWorld()->ServerTravel("/Game/TP1/Maps/FreeMap");
}

void AGameModeLobby::StartCountdownTimer()
{
	AMyGameState* GS = GetGameState<AMyGameState>();
	if (GS)
	{
		GS->TimerEnd = GetWorld()->GetTimeSeconds() + 10;
		GS->OnRep_TimerEnd();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
			FString::Printf(TEXT("Timer End Modified")));
	}
}
