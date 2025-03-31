// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerGameInstance.h"

#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"
#include "Interfaces/OnlineAchievementsInterface.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Kismet/GameplayStatics.h"

IOnlineAchievementsPtr UMultiplayerGameInstance::GetAchievementsInterface()
{
	if (IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		return Subsystem->GetAchievementsInterface();
	}
	return nullptr;
}

void UMultiplayerGameInstance::UnlockAchievement(FString AchievementName)
{
	IOnlineAchievementsPtr Achievements = GetAchievementsInterface();
	if (Achievements.IsValid())
	{
		IOnlineIdentityPtr Identity = IOnlineSubsystem::Get()->GetIdentityInterface();
		FUniqueNetIdPtr PlayerId = Identity->GetUniquePlayerId(0);

		if (PlayerId.IsValid())
		{
			TArray<FOnlineAchievement> PlayerAchievements;
			Achievements->GetCachedAchievements(*PlayerId, PlayerAchievements);

			float NewProgress = 100.0f; // Valeur par défaut

			for (const FOnlineAchievement& Achievement : PlayerAchievements)
			{
				if (Achievement.Id == AchievementName)
				{
					// Inverser la progression
					NewProgress = (Achievement.Progress >= 100.0f) ? 0.0f : 100.0f;
					break;
				}
			}

			FOnlineAchievementsWriteRef AchievementWriteObject = MakeShareable(new FOnlineAchievementsWrite());
			AchievementWriteObject->SetFloatStat(*AchievementName, NewProgress);

			Achievements->WriteAchievements(*PlayerId, AchievementWriteObject,
				FOnAchievementsWrittenDelegate::CreateUObject(this, &UMultiplayerGameInstance::OnAchievementUnlocked));
		}
	}
}

void UMultiplayerGameInstance::OnAchievementUnlocked(const FUniqueNetId& PlayerId, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Achievement unlocked"));
	}
}

void UMultiplayerGameInstance::OnQueryAchievementsComplete(const FUniqueNetId& PlayerId, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("QueryAchievementsComplete"));

	}
}

void UMultiplayerGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("Init"));


	if (IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		Session = Subsystem->GetSessionInterface();
		if (Session.IsValid())
		{
			Session->OnCreateSessionCompleteDelegates.AddUObject(this, &UMultiplayerGameInstance::OnCreateSessionComplete);
			Session->OnFindSessionsCompleteDelegates.AddUObject(this, &UMultiplayerGameInstance::OnFindSessionsComplete);
			Session->OnJoinSessionCompleteDelegates.AddUObject(this,&UMultiplayerGameInstance::OnJoinSessionComplete);
		}
	}
	IOnlineAchievementsPtr Achievements = GetAchievementsInterface();
	if (Achievements.IsValid())
	{
		IOnlineIdentityPtr Identity = IOnlineSubsystem::Get()->GetIdentityInterface();
		FUniqueNetIdPtr PlayerId = Identity->GetUniquePlayerId(0);
            
		if (PlayerId.IsValid())
		{
			Achievements->QueryAchievements(*PlayerId, FOnQueryAchievementsCompleteDelegate::CreateUObject(this, &UMultiplayerGameInstance::OnQueryAchievementsComplete));
		}
	}
}

void UMultiplayerGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("CreateSessionComplete"));

		GetWorld()->ServerTravel(TEXT("/Game/TP1/Maps/FreeMap?listen"));
	}
}

void UMultiplayerGameInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;
		FOnlineSessionSearchResult* SearchResultPtr = const_cast<FOnlineSessionSearchResult*>(&SearchResults[0]);
		SearchResultPtr->Session.SessionSettings.bUsesPresence = true;
		SearchResultPtr->Session.SessionSettings.bUseLobbiesIfAvailable = true;
		if (!SearchResults.IsEmpty())
		{
			
			UE_LOG(LogTemp, Warning, TEXT("FindSessionComplete, Name : %s"), *SearchResults[0].Session.OwningUserName);
			Session->JoinSession(0, TEXT("ENSIIEUQACSteam"), *SearchResultPtr);
		}
	}
}

void UMultiplayerGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	UE_LOG(LogTemp, Warning, TEXT("JoinSessionComplete, Name : %s"), *SessionName.ToString());

	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		FString JoinAdress;
		Session->GetResolvedConnectString(SessionName, JoinAdress);
		if (!JoinAdress.IsEmpty())
		{
			UE_LOG(LogTemp, Warning, TEXT("Joining"));

			PC->ClientTravel(JoinAdress, ETravelType::TRAVEL_Absolute);
		}
	}

	UnlockAchievement("ACH_WIN_100_GAMES");
}

void UMultiplayerGameInstance::HostSession()
{
	FOnlineSessionSettings SessionSettings;

	SessionSettings.bIsDedicated = false;
	SessionSettings.bIsLANMatch = false;
	SessionSettings.NumPublicConnections = 2;
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bAllowJoinViaPresence = true;
	SessionSettings.bUseLobbiesIfAvailable = true;
	SessionSettings.bAllowInvites = true;
	SessionSettings.bUsesPresence = true;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.Set(FName("MatchType"), FString("SteamTPAchievements"), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	UE_LOG(LogTemp, Warning, TEXT("CreateSession"));

	Session->CreateSession(0, TEXT("ENSIIEUQACSteam"), SessionSettings);
}

void UMultiplayerGameInstance::JoinSession()
{
	
	
	UE_LOG(LogTemp, Warning, TEXT("JoinSession"));

	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->bIsLanQuery = false;
	SessionSearch->QuerySettings.Set(FName("MatchType"), FString("SteamTPAchievements"), EOnlineComparisonOp::Equals);
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	
	Session->FindSessions(0, SessionSearch.ToSharedRef());
}
