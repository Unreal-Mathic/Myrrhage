// Fill out your copyright notice in the Description page of Project Settings.

#include "MyrrhagePrivate.h"
#include "EquipmentManager.h"

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
bool UEquipmentManager::CheckEquipped(class UStatManager* CharacterStats, class ABaseEquipment* CurrentEquipped, class ABaseEquipment* Equipment)
{
	FString message = "";
	if (CurrentEquipped == Equipment)
	{
		return false;
	}
	else if (CurrentEquipped == nullptr)
	{
		CharacterStats->AddStats(Equipment);
		return true;
	}
	else if (Equipment->GetEquippedOn() == EEquippedOn::ETwoHanded)
	{
		if (RightHand != nullptr && LeftHand != nullptr)
		{
			Unequip(CharacterStats, RightHand);
			Unequip(CharacterStats, LeftHand);
			CharacterStats->AddStats(Equipment);
			return true;
		}
		return false;
	}
	else if (CurrentEquipped != nullptr)
	{
		Unequip(CharacterStats, CurrentEquipped);
		CharacterStats->AddStats(Equipment);
		return true;
	}
	return false;
}

void UEquipmentManager::Equip(class UStatManager* CharacterStats, class ABaseEquipment* Equipment)
{
	// equip it in the right character slot
	switch (Equipment->GetEquippedOn())
	{
	case EEquippedOn::EHead:
		if (CheckEquipped(CharacterStats, HeadArmor, Equipment)){ HeadArmor = Equipment; }
		break;
	case EEquippedOn::EBody:
		if (CheckEquipped(CharacterStats, BodyArmor, Equipment)){ BodyArmor = Equipment; }
		break;
	case EEquippedOn::EHands:
		if (CheckEquipped(CharacterStats, HandArmor, Equipment)){ HandArmor = Equipment; }
		break;
	case EEquippedOn::ELegs:
		if (CheckEquipped(CharacterStats, LegArmor, Equipment)){ LegArmor = Equipment; }
		break;
	case EEquippedOn::EFeet:
		if (CheckEquipped(CharacterStats, FeetArmor, Equipment)){ FeetArmor = Equipment; }
		break;
	case EEquippedOn::ERightHand:
		if (CheckEquipped(CharacterStats, RightHand, Equipment)){ RightHand = Equipment; }
		break;
	case EEquippedOn::ELeftHand:
		if (CheckEquipped(CharacterStats, LeftHand, Equipment)){ LeftHand = Equipment; }
		break;
	case EEquippedOn::ETwoHanded:
		if (CheckEquipped(CharacterStats, RightHand, Equipment)){ RightHand = Equipment; }
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
