// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP1GameMode.h"
#include "TP1Character.h"
#include "UObject/ConstructorHelpers.h"

ATP1GameMode::ATP1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
