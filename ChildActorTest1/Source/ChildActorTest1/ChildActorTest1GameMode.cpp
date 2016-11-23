// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "ChildActorTest1.h"
#include "ChildActorTest1GameMode.h"
#include "ChildActorTest1PlayerController.h"
#include "ChildActorTest1Character.h"

AChildActorTest1GameMode::AChildActorTest1GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AChildActorTest1PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}