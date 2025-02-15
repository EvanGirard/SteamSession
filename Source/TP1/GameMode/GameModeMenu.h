// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeMenu.generated.h"

/**
 * 
 */
UCLASS()
class TP1_API AGameModeMenu : public AGameModeBase
{
	GENERATED_BODY()

	AGameModeMenu();
	
	virtual FString InitNewPlayer(APlayerController* NewPlayerController,const FUniqueNetIdRepl& UniqueId,const FString& Options,const FString& Portal) override;
};
