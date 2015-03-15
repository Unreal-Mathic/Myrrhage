// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyrrhageGlobals.h"
#include "BaseItem.h"
#include "BaseEquipment.generated.h"

/**
*
*/
UCLASS()
class MYRRHAGE_API ABaseEquipment : public ABaseItem
{
	GENERATED_BODY()

public:
	ABaseEquipment(const class FObjectInitializer& PCIP);

	/* Property getters and setters */
	TArray<FStatStruct> GetStats();

	FStatStruct GetRequiredStat();

	void SetEquippedOn(EEquippedOn);
	EEquippedOn GetEquippedOn();

	EClass GetClassType();
	/* End property getters and setters */

	virtual void PickedUp() override;

	// Override the ABaseItem OnPickUp
	void OnPickedUp_Implementation() override;

protected:
	// Equipment can have more than one stat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	TArray<FStatStruct> Stats;

	// Required stat a character needs to equip this item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FStatStruct RequiredStat;

	// The body part this item is equipped on
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	EEquippedOn EquippedOn;

	// Only characters of this class can weat this item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	EClass ClassType;
};
