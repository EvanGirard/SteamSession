// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TP1_API UMyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void StartTimer(float TimeLeft);

	FTimerHandle TimerHandle;
	float CurrentTimeLeft;
	
	UFUNCTION()
	void UpdateTimer();

protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* TimerTextBlock;
};
