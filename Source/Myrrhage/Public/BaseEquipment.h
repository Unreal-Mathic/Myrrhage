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

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	TArray<FStatStruct> Stats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	FStatStruct RequiredStat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	TEnumAsByte<EEquippedOn> EquippedOn;
public:
	ABaseEquipment(const class FObjectInitializer& PCIP);

	TEnumAsByte<EEquippedOn> GetEquippedOn();
	TArray<FStatStruct> GetStats();

	void OnPickUp_Implementation() override;
};
