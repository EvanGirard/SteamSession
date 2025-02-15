// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MyGameState.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimerUpdated, float, TimeLeft);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimerEnd);

UCLASS()
class TP1_API AMyGameState : public AGameState
{
	GENERATED_BODY()

public:
	AMyGameState();

	UPROPERTY(ReplicatedUsing=OnRep_TimerEnd)
	float TimerEnd;

	UPROPERTY(Replicated)
	bool bTimerStarted = false;

	UFUNCTION()
	void OnRep_TimerEnd();

	UPROPERTY(BlueprintAssignable)
	FOnTimerUpdated OnTimerUpdated;

	UPROPERTY(BlueprintAssignable)
	FOnTimerEnd OnTimerEnd;

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerBroadcastTimerEnd();
	void ServerBroadcastTimerEnd_Implementation();
	bool ServerBroadcastTimerEnd_Validate() { return true; }

};
