// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSpriteActor.h"
#include "BaseItem.generated.h"

#pragma region ENUMS
UENUM(BlueprintType)
namespace EItem
{
	enum Type
	{
		EArmor	UMETA(DisplayName = "Armor"),
		EWeapon	UMETA(DisplayName = "Weapon"),
		EPotion	UMETA(DisplayName = "Potion")
	};
}

UENUM(BlueprintType)
namespace EStat
{
	enum Type
	{
		EMight			UMETA(DisplayName = "Might"),
		EKnowledge		UMETA(DisplayName = "Knowledge"),
		EPresence		UMETA(DisplayName = "Presence"),
		EResistance		UMETA(DisplayName = "Resistance"),
		EAgility		UMETA(DisplayName = "Agility")
	};
}
#pragma endregion ENUMS

/**
 * 
 */
UCLASS(abstract)
class MYRRHAGE_API ABaseItem : public APaperSpriteActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items)
	TEnumAsByte<EItem::Type> m_ItemType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items)
	FString m_Name;

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnPickUp();

	FString GetItemName();
};
