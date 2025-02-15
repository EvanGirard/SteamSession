// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeMenu.h"

#include "Kismet/GameplayStatics.h"
#include "TP1/TP1Character.h"
#include "TP1/TP1/MyPlayerState.h"

AGameModeMenu::AGameModeMenu()
{
}

FString AGameModeMenu::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
                                     const FString& Options, const FString& Portal)
{
	if (ATP1Character* PlayerCharacter = Cast<ATP1Character>(UGameplayStatics::GetActorOfClass(GetWorld(),ATP1Character::StaticClass())))
	{
		NewPlayerController->GetPlayerState<AMyPlayerState>()->OnSkinIndexChanged.AddDynamic(PlayerCharacter, &ATP1Character::ApplySkin);
	
	}
	return Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
}
