// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseItem.h"
#include "BaseEquipment.generated.h"

#pragma region STRUCTS
USTRUCT(BlueprintType)
struct FStatStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items)
	float StatValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items)
	TEnumAsByte<EStat::Type> StatType;

	void SetValue(float value){ StatValue = value; }
	float GetValue(){ return StatValue; }
	void SetType(TEnumAsByte<EStat::Type> type){ StatType = type; }
	TEnumAsByte<EStat::Type> GetType(){ return StatType; }

	FStatStruct()
	{

	}
};
#pragma endregion STRUCTS

/**
*
*/
UCLASS()
class MYRRHAGE_API ABaseEquipment : public ABaseItem
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items)
	TArray<FStatStruct> m_Stats;

public:
	void OnPickUp_Implementation() override;
};
