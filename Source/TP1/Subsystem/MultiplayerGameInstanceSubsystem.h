// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MultiplayerGameInstanceSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TP1_API UMultiplayerGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()


public:

	IOnlineSessionPtr Session;
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", AdvancedDisplay = "1"), Category = "Game")
	void HostGame();

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", AdvancedDisplay = "1"), Category = "Game")
	bool JoinGame(FString Ip);

	UFUNCTION(BlueprintCallable)
	void HostSession();

	UFUNCTION(BlueprintCallable)
	void JoinSession();
};
