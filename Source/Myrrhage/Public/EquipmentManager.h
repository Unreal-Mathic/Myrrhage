// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseEquipment.h"
#include "BaseWeapon.h"
#include "StatManager.h"
#include "InventoryWidget.h"

#include "Object.h"
#include "EquipmentManager.generated.h"

/**
 * 
 */
UCLASS()
class MYRRHAGE_API UEquipmentManager : public UObject
{
	GENERATED_BODY()
public:
	UEquipmentManager();

	/* Checking for new, same, or non-empty equipment slot */
	void CheckEquipped(class UStatManager*, class ABaseEquipment**, class ABaseEquipment*);

	// Equip the armor or weapon and add the stats
	void Equip(class UStatManager*, class ABaseEquipment*, EHandedness);

	// Unequip the armor or weapon and remove the stats
	void Unequip(class UStatManager*, class ABaseEquipment*);

	// Check if any is equipped in the left or right hand
	bool HasWeapon();

	/* Return the equipped weapon (based on handedness)
	 * TODO implement the dual-wielding attacks? */
	ABaseWeapon* GetWeapon();
protected:
	// Head armor slot
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	ABaseEquipment* HeadArmor;

	// Body armor slot
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	ABaseEquipment* BodyArmor;

	// Hand armor slot
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	ABaseEquipment* HandArmor;

	// Leg armor slot
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	ABaseEquipment* LegArmor;

	// Feet armor slot
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	ABaseEquipment* FeetArmor;

	// Left weapon slot
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	ABaseEquipment* LeftHand;

	// Right weapon slot
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	ABaseEquipment* RightHand;

	// Opening the inventory GUI
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	TSubclassOf<UUserWidget> WidgetTemplate;

	// Instance of widget
	UPROPERTY()
	UUserWidget* WidgetInstance;

private:
	// Initialize the equipment only gets called from this class
	void InitializeCharacterEquipment();
};
