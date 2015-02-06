// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseItem.h"
#include "BaseEquipment.h"
#include "InventoryWidget.h"

#include "Object.h"
#include "EquipmentManager.generated.h"

#pragma region CHAR_STRUCTS
USTRUCT(BlueprintType, Category = Equipment)
struct FEquipment
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ABaseEquipment* Equipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EEquippedOn> Accepted;

	FEquipment(){}
	FEquipment(TEnumAsByte<EEquippedOn> accepted)
	{
		Equipment = nullptr;
		Accepted = accepted;
	}
};
#pragma region CHAR_STRUCTS

/**
 * 
 */
UCLASS()
class MYRRHAGE_API UEquipmentManager : public UObject
{
	GENERATED_BODY()
	
protected:
	// The array of equipment
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	FEquipment CharacterEquipment[7];

	FEquipment* HeadArmor = nullptr;
	FEquipment* BodyArmor = nullptr;
	FEquipment* HandArmor = nullptr;
	FEquipment* LegArmor = nullptr;
	FEquipment* FeetArmor = nullptr;
	FEquipment* LeftHand = nullptr;
	FEquipment* RightHand = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	TSubclassOf<UUserWidget> WidgetTemplate;

	UPROPERTY()
	UUserWidget* WidgetInstance;
	
public:
	UEquipmentManager();

	bool CheckEquipped(struct FEquipment*, class ABaseEquipment*);
	bool Equip(class ABaseEquipment*);
	void Unequip(struct FEquipment*);

	void InitializeCharacterEquipment();
};
