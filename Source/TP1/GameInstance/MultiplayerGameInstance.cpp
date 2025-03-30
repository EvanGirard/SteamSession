// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerGameInstance.h"

#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Kismet/GameplayStatics.h"

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
		/*FOnlineSessionSearchResult* SearchResultPtr = const_cast<FOnlineSessionSearchResult*>(&SearchResults[0]);
		SearchResultPtr->Session.SessionSettings.bUsesPresence = true;
		SearchResultPtr->Session.SessionSettings.bUseLobbiesIfAvailable = true;*/
		if (!SearchResults.IsEmpty())
		{	UE_LOG(LogTemp, Warning, TEXT("FindSessionComplete"));

			Session->JoinSession(0, TEXT("ENSIIEGigeUQAC"), SearchResults[0]);
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
			UE_LOG(LogTemp, Warning, TEXT("Joining"
								 ""));

			PC->ClientTravel(JoinAdress, ETravelType::TRAVEL_Absolute);
		}
	}
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
	UE_LOG(LogTemp, Warning, TEXT("CreateSession"));

	Session->CreateSession(0, TEXT("ENSIIEGigeUQAC"), SessionSettings);
}

void UMultiplayerGameInstance::JoinSession()
{
	UE_LOG(LogTemp, Warning, TEXT("JoinSession"));

	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->bIsLanQuery = false;
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	
	Session->FindSessions(0, SessionSearch.ToSharedRef());
}
