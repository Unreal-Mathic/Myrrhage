// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MyrrhagePrivate.h"
#include "MyrrhageGameMode.h"
#include "MyrrhageCharacter.h"
#include "Kismet/GameplayStatics.h"

AMyrrhageGameMode::AMyrrhageGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our character
	DefaultPawnClass = AMyrrhageCharacter::StaticClass();
}

void AMyrrhageGameMode::Tick(float DeltaSeconds)
{
	AMyrrhageCharacter* MyCharacter = Cast<AMyrrhageCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	//if the character still has health
	if (MyCharacter->GetCharacterHealth() > 0.0f)
	{
		
	}
	else
	{
		SetCurrentState(EMyrrhagePlayState::EGameOver);
	}
}

void AMyrrhageGameMode::SetCurrentState(EMyrrhagePlayState NewState)
{
	CurrentState = NewState;

	HandleNewState(NewState);
}

void AMyrrhageGameMode::HandleNewState(EMyrrhagePlayState NewState)
{
	switch (NewState)
	{
	case EMyrrhagePlayState::EPlaying:
		/*for (AEnemyCharacter* Volume : SpawnVolumeActors)
		{
			Volume->EnableSpawning();
		}*/
		break;
	case EMyrrhagePlayState::EGameOver:
	{
		/*for (AEnemyCharacter* Volume : SpawnVolumeActors)
		{
			Volume->DisableSpawning();
		}*/
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		PlayerController->SetCinematicMode(true, true, true);
	}
	break;
	case EMyrrhagePlayState::EUnknown:
	default:
		//do nothing
		break;

	}
}

void AMyrrhageGameMode::BeginPlay()
{
	Super::BeginPlay();

	//find all enemy actors
	TArray<AActor*> FoundActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyCharacter::StaticClass(), FoundActors);

	for (auto Actor : FoundActors)
	{
		AEnemyCharacter* EnemyActor = Cast<AEnemyCharacter>(Actor);
		if (EnemyActor)
		{
			EnemyActors.Add(EnemyActor);
		}
	}

	SetCurrentState(EMyrrhagePlayState::EPlaying);
}
