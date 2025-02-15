// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerGameInstanceSubsystem.h"

#include <regex>

#include "TP1/TP1/MyPlayerState.h"

void UMultiplayerGameInstanceSubsystem::HostGame()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		AMyPlayerState* PlayerState = PC->GetPlayerState<AMyPlayerState>();
		if (PlayerState)
		{
			int32 SelectedSkinIndex = PlayerState->GetSkinIndex();
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
			FString::Printf(TEXT("Host Before Travel: %d"), SelectedSkinIndex));
    
			FString TravelURL = FString::Printf(TEXT("/Game/TP1/Maps/LobbyMap2?listen?SkinIndex=%d"), SelectedSkinIndex);

			PC->ClientTravel(TravelURL, TRAVEL_Absolute);
		}
		//PC->ClientTravel("/Game/TP1/Maps/LobbyMap?listen?SkinIndex=2",TRAVEL_Absolute);
	}
}

bool UMultiplayerGameInstanceSubsystem::JoinGame(FString Ip)
{
	const std::regex ipPattern(R"(^(\d{1,3}\.){3}\d{1,3}$)");

	if (Ip.IsEmpty() || !std::regex_match(TCHAR_TO_UTF8(*Ip), ipPattern))
	{
		return false;
	}
	
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
			AMyPlayerState* PlayerState = PC->GetPlayerState<AMyPlayerState>();
			if (PlayerState)
			{
				int32 SelectedSkinIndex = PlayerState->GetSkinIndex();
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
				FString::Printf(TEXT("Before Travel: %d"), SelectedSkinIndex));

				FString TravelURL = FString::Printf(TEXT("?SkinIndex=%d"), SelectedSkinIndex);
				TravelURL = Ip + TravelURL;

				PC->ClientTravel(TravelURL, TRAVEL_Absolute);
				return true;
			}
		//PC->ClientTravel(Ip, ETravelType::TRAVEL_Absolute);
		return true;
	}
	return false;
}
