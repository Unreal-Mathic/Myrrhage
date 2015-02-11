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
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	FStatStruct Agility;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	FStatStruct Knowledge;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	FStatStruct Might;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	FStatStruct Presence;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	FStatStruct Resistance;

	void InitializeStats();
	
	UStatManager();

public:
	FString GetCharacterStats();

	void CalculateStats(class ABaseEquipment*);
	void AddStats(class ABaseEquipment*);
	void RemoveStats(class ABaseEquipment*);
};
