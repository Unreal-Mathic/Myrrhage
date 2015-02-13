// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseEquipment.h"
#include "MyrrhageGlobals.h"

#include "Object.h"
#include "StatManager.generated.h"

/**
 * 
 */
UCLASS()
class MYRRHAGE_API UStatManager : public UObject
{
	GENERATED_BODY()
public:
	UStatManager();

	// Print character stats (debugging)
	FString GetCharacterStats();

	// No implementation yet
	void CalculateStats(class ABaseEquipment*);

	// Add equipment stat value to corresponding stat
	void AddStats(class ABaseEquipment*);

	// Remove equipment stat value to corresponding stat
	void RemoveStats(class ABaseEquipment*);
	
protected:
	// How fast the character can move/attack and adds to energy
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	FStatStruct Agility;

	// Character's magic damage, mana, and hacking abilities
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	FStatStruct Knowledge;

	// Character's melee strength and adds to energy
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	FStatStruct Might;

	// Character's leadership ability and bartering
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	FStatStruct Presence;

	// Take less damage, blocking, parrying, less stuns (time and frequency)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	FStatStruct Resistance;

	// Initialize the stat properties
	void InitializeStats();
};
