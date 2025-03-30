// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MultiplayerGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TP1_API UMultiplayerGameInstance : public UGameInstance
{
	GENERATED_BODY()

	IOnlineSessionPtr Session;

	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	virtual void Init() override;
	virtual void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	virtual void OnFindSessionsComplete(bool bWasSuccessful);
	virtual void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	UFUNCTION(BlueprintCallable)
	void HostSession();

	UFUNCTION(BlueprintCallable)
	void JoinSession();
};
