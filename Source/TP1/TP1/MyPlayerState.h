// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkinIndexChanged, int32, NewSkinIndex);

UCLASS()
class TP1_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	AMyPlayerState();

	UPROPERTY(BlueprintAssignable, Category = "Skin")
	FOnSkinIndexChanged OnSkinIndexChanged;
	
	UFUNCTION(BlueprintCallable)
	int32 GetSkinIndex();
	
	UFUNCTION(BlueprintCallable)
	void SetSkinIndex(int32 index);
	
protected:
	UFUNCTION()
	void OnRep_SkinIndex();
	
	UPROPERTY(ReplicatedUsing=OnRep_SkinIndex)
	int32 SelectedSkinIndex = 0;
	
	UFUNCTION(Server,Reliable)
	void Server_changeSkinIndex(int32 index);
	
	virtual void CopyProperties(APlayerState* PlayerState) override;
};
