// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "TP1/TP1Character.h"

AMyPlayerState::AMyPlayerState()
{
	bReplicates = true;
}

int32 AMyPlayerState::GetSkinIndex()
{
	return SelectedSkinIndex;
}

void AMyPlayerState::SetSkinIndex(int32 index)
{
	if (HasAuthority())
	{
		SelectedSkinIndex = index;
		OnSkinIndexChanged.Broadcast(SelectedSkinIndex);
	}
	else
	{
		Server_changeSkinIndex(index);
	}
}

void AMyPlayerState::OnRep_SkinIndex()
{
	OnSkinIndexChanged.Broadcast(SelectedSkinIndex);
}

void AMyPlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	AMyPlayerState* TargetPlayerState = Cast<AMyPlayerState>(PlayerState);
	if (TargetPlayerState)
	{
		TargetPlayerState->SetSkinIndex((SelectedSkinIndex));
	}
}

void AMyPlayerState::Server_changeSkinIndex_Implementation(int32 index)
{
	SetSkinIndex(index);
}

void AMyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyPlayerState, SelectedSkinIndex);
}