// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameModeLobby.generated.h"

/**
 * 
 */
UCLASS()
class TP1_API AGameModeLobby : public AGameMode
{
	GENERATED_BODY()
public:
	AGameModeLobby();

	virtual void BeginPlay() override;
	
	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual FString InitNewPlayer(APlayerController* NewPlayerController,const FUniqueNetIdRepl& UniqueId,const FString& Options,const FString& Portal) override;

	void StartGame();
private:

	UPROPERTY()
	int32 DefaultSelectedSkinIndex = 0;
	
	void StartCountdownTimer();
};
