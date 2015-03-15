// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "EnemyCharacter.h"
#include "GameFramework/GameMode.h"
#include "MyrrhageGameMode.generated.h"

// The GameMode defines the game being played. It governs the game rules, scoring, what actors
// are allowed to exist in this game type, and who may enter the game.
//
// This game mode just sets the default pawn to be the MyCharacter asset, which is a subclass of MyrrhageCharacter

enum class EMyrrhagePlayState : short
{
	EPlaying,
	EGameOver,
	EUnknown
};

UCLASS(minimalapi)
class AMyrrhageGameMode : public AGameMode
{
	GENERATED_BODY()

	virtual void Tick(float DeltaSeconds) override;

	EMyrrhagePlayState GetCurrentState() const;

	void SetCurrentState(EMyrrhagePlayState NewState);

	virtual void BeginPlay() override;
public:
	AMyrrhageGameMode(const FObjectInitializer& ObjectInitializer);

	TArray<AEnemyCharacter*> EnemyActors;

	EMyrrhagePlayState CurrentState;

	void HandleNewState(EMyrrhagePlayState NewState);

};

FORCEINLINE EMyrrhagePlayState AMyrrhageGameMode::GetCurrentState() const
{
	return CurrentState;
}
