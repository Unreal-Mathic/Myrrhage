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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	TArray<FStatStruct> Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FStatStruct RequiredStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	TEnumAsByte<EEquippedOn> EquippedOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	TEnumAsByte<EClass> ClassType;
public:
	ABaseEquipment(const class FObjectInitializer& PCIP);

	TArray<FStatStruct> GetStats();

	FStatStruct GetRequiredStat();

	void SetEquippedOn(EEquippedOn);
	TEnumAsByte<EEquippedOn> GetEquippedOn();
	
	TEnumAsByte<EClass> GetClassType();

	void OnPickUp_Implementation() override;
};
