// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyWidget.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TP1_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UFUNCTION()
	void UpdateTimerUI(float TimeLeft);

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UMyWidget> TimerWidgetClass;


private:
	UPROPERTY()
	UMyWidget* TimerWidget;
};
