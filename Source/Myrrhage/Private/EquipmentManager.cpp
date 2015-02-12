// Fill out your copyright notice in the Description page of Project Settings.

#include "MyrrhagePrivate.h"
#include "EquipmentManager.h"
#include <time.h>       /* time */

UEquipmentManager::UEquipmentManager()
{
	InitializeCharacterEquipment();
}

void UEquipmentManager::InitializeCharacterEquipment()
{
	HeadArmor = nullptr;
	BodyArmor = nullptr;
	HandArmor = nullptr;
	LegArmor = nullptr;
	FeetArmor = nullptr;
	LeftHand = nullptr;
	RightHand = nullptr;
}

//TODO take the item out of the inventory
void UEquipmentManager::CheckEquipped(class UStatManager* CharacterStats, class ABaseEquipment** CurrentEquipped, class ABaseEquipment* Equipment)
{
	if (*CurrentEquipped == Equipment)
	{
		return;
	}
	else if (*CurrentEquipped == nullptr)
	{
		*CurrentEquipped = Equipment;
		CharacterStats->AddStats(Equipment);
	}
	else if (Equipment->GetEquippedOn() == EEquippedOn::ETwoHanded)
	{
		if (RightHand != nullptr && LeftHand != nullptr)
		{
			Unequip(CharacterStats, RightHand);
			Unequip(CharacterStats, LeftHand);
			*CurrentEquipped = Equipment;
			CharacterStats->AddStats(Equipment);
		}
		return;
	}
	else if (*CurrentEquipped != nullptr)
	{
		Unequip(CharacterStats, *CurrentEquipped);
		*CurrentEquipped = Equipment;
		CharacterStats->AddStats(Equipment);
	}
}

void UEquipmentManager::Equip(class UStatManager* CharacterStats, class ABaseEquipment* Equipment, TEnumAsByte<EHandedness> Handedness)
{
	// equip it in the right character slot
	switch (Equipment->GetEquippedOn())
	{
	case EEquippedOn::EHead:
		CheckEquipped(CharacterStats, &HeadArmor, Equipment);
		break;
	case EEquippedOn::EBody:
		CheckEquipped(CharacterStats, &BodyArmor, Equipment);
		break;
	case EEquippedOn::EHands:
		CheckEquipped(CharacterStats, &HandArmor, Equipment);
		break;
	case EEquippedOn::ELegs:
		CheckEquipped(CharacterStats, &LegArmor, Equipment);
		break;
	case EEquippedOn::EFeet:
		CheckEquipped(CharacterStats, &FeetArmor, Equipment);
		break;
	case EEquippedOn::ERightHand:
	case EEquippedOn::ELeftHand:
	case EEquippedOn::ETwoHanded:
		if (Handedness == EHandedness::ELeftHanded)
		{
			CheckEquipped(CharacterStats, &LeftHand, Equipment);
		}
		else if (Handedness == EHandedness::ERightHanded)
		{
			CheckEquipped(CharacterStats, &RightHand, Equipment);
		}
		else if (Handedness == EHandedness::EAmbidextrous)
		{
			/* initialize random seed: */
			srand(time(NULL));
			int hand = rand() % 2 + 1;
			if (hand == 1)
				CheckEquipped(CharacterStats, &RightHand, Equipment);
			else
				CheckEquipped(CharacterStats, &LeftHand, Equipment);
		}
		break;
	default:
		break;
	}
}

void UEquipmentManager::Unequip(class UStatManager* CharacterStats, class ABaseEquipment* Current)
{
	//TODO return the item to the inventory
	CharacterStats->RemoveStats(Current);
	Current = nullptr;
}

bool UEquipmentManager::HasWeapon()
{
	if (LeftHand == nullptr && RightHand == nullptr)
		return false;
	return true;
}

ABaseWeapon* UEquipmentManager::GetWeapon()
{
	if (LeftHand != nullptr)
	{
		return dynamic_cast<ABaseWeapon*>(LeftHand);
	}
	else if (RightHand != nullptr)
	{
		return dynamic_cast<ABaseWeapon*>(RightHand);
	}
	else
	{
		return nullptr;
	}
}
