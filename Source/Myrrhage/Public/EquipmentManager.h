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
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	ABaseEquipment* HeadArmor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	ABaseEquipment* BodyArmor;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	ABaseEquipment* HandArmor;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	ABaseEquipment* LegArmor;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	ABaseEquipment* FeetArmor;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	ABaseEquipment* LeftHand;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	ABaseEquipment* RightHand;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	TSubclassOf<UUserWidget> WidgetTemplate;

	UPROPERTY()
	UUserWidget* WidgetInstance;

	void InitializeCharacterEquipment();
	
public:
	UEquipmentManager();

	void CheckEquipped(class UStatManager*, class ABaseEquipment**, class ABaseEquipment*);
	void Equip(class UStatManager*, class ABaseEquipment*, TEnumAsByte<EHandedness>);
	void Unequip(class UStatManager*, class ABaseEquipment*);
	bool HasWeapon();
	ABaseWeapon* GetWeapon();
};
