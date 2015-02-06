// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyrrhageGlobals.generated.h"

#pragma region ENUMS
UENUM(BlueprintType, Category = Items)
enum class EItem : uint8
{
	EArmor	UMETA(DisplayName = "Armor"),
	EWeapon	UMETA(DisplayName = "Weapon"),
	EPotion	UMETA(DisplayName = "Potion")
};

UENUM(BlueprintType, Category = Stats)
enum class EStat : uint8
{
	EMight			UMETA(DisplayName = "Might"),
	EKnowledge		UMETA(DisplayName = "Knowledge"),
	EPresence		UMETA(DisplayName = "Presence"),
	EResistance		UMETA(DisplayName = "Resistance"),
	EAgility		UMETA(DisplayName = "Agility")
};

UENUM(BlueprintType, Category = Equipment)
enum class EEquippedOn : uint8
{
	EHead			UMETA(DisplayName = "Head Armor"),
	EBody			UMETA(DisplayName = "Body Armor"),
	ELegs			UMETA(DisplayName = "Leg Armor"),
	EFeet			UMETA(DisplayName = "Feet Armor"),
	EHands			UMETA(DisplayName = "Hand Armor"),
	ELeftHand		UMETA(DisplayName = "Left Hand"),
	ERightHand		UMETA(DisplayName = "Right Hand"),
	ETwoHanded		UMETA(DisplayName = "Two-handed")
};
#pragma endregion ENUMS

#pragma region STRUCTS
USTRUCT(BlueprintType)
struct FStatStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items)
	float StatValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items)
	TEnumAsByte<EStat> StatType;

	void SetValue(float value){ StatValue = value; }
	float GetValue(){ return StatValue; }
	void SetType(TEnumAsByte<EStat> type){ StatType = type; }
	TEnumAsByte<EStat> GetType(){ return StatType; }
	void AddToValue(float value)
	{ 
		StatValue += value;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::FromInt(StatValue));
	}

	FString GetEnumAsString()
	{
		FString stat;
		switch (StatType)
		{
		case EStat::EAgility:
			stat = TEXT("Agility ");
			break;
		case EStat::EKnowledge:
			stat = TEXT("Knowledge ");
			break;
		case EStat::EMight:
			stat = TEXT("Might ");
			break;
		case EStat::EPresence:
			stat = TEXT("Presence ");
			break;
		case EStat::EResistance:
			stat = TEXT("Resistance ");
			break;
		default:
			stat = TEXT("UNKNOWN");
			break;
		}

		return stat + FString::FromInt(StatValue);
	}

	FStatStruct(){}
	FStatStruct(TEnumAsByte<EStat> type)
	{
		StatType = type;
		StatValue = (rand() % 10) + 1;
	}

	FStatStruct(TEnumAsByte<EStat> type, float value)
	{
		StatType = type;
		StatValue = value;
	}
};
#pragma endregion STRUCTS

/**
 * 
 */
class MYRRHAGE_API MyrrhageGlobals
{
	
};
