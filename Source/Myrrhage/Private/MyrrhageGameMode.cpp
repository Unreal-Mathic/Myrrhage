// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MyrrhagePrivate.h"
#include "MyrrhageGameMode.h"
#include "MyrrhageCharacter.h"

AMyrrhageGameMode::AMyrrhageGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our character
	DefaultPawnClass = AMyrrhageCharacter::StaticClass();
}
