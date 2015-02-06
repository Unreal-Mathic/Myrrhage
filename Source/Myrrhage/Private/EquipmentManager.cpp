// Fill out your copyright notice in the Description page of Project Settings.

#include "MyrrhagePrivate.h"
#include "EquipmentManager.h"

UEquipmentManager::UEquipmentManager()
{
	InitializeCharacterEquipment();
}

void UEquipmentManager::InitializeCharacterEquipment()
{
	CharacterEquipment[0] = FEquipment(EEquippedOn::EHead);
	CharacterEquipment[1] = FEquipment(EEquippedOn::EBody);
	CharacterEquipment[2] = FEquipment(EEquippedOn::EHands);
	CharacterEquipment[3] = FEquipment(EEquippedOn::ELegs);
	CharacterEquipment[4] = FEquipment(EEquippedOn::EFeet);
	CharacterEquipment[5] = FEquipment(EEquippedOn::ELeftHand);
	CharacterEquipment[6] = FEquipment(EEquippedOn::ERightHand);

	HeadArmor = &CharacterEquipment[0];
	BodyArmor = &CharacterEquipment[1];
	HandArmor = &CharacterEquipment[2];
	LegArmor = &CharacterEquipment[3];
	FeetArmor = &CharacterEquipment[4];
	LeftHand = &CharacterEquipment[5];
	RightHand = &CharacterEquipment[6];
}

bool UEquipmentManager::CheckEquipped(struct FEquipment* CurrentEquipped, class ABaseEquipment* Equipment)
{
	FString msg;
	if (CurrentEquipped->Equipment == nullptr)
	{
		CurrentEquipped->Equipment = Equipment;
		msg = "NEW EQUIPMENT";
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, msg);
		return true;
	}
	else if (CurrentEquipped->Equipment == Equipment) 
	{
		msg = "SAME EQUIPMENT";
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, msg);
		return false;
	}
	else if (Equipment->GetEquippedOn() == EEquippedOn::ETwoHanded)
	{
		if (RightHand->Equipment != nullptr && LeftHand->Equipment != nullptr)
		{
			Unequip(RightHand);
			Unequip(LeftHand);
			CurrentEquipped->Equipment = Equipment;
			return true;
		}
		return false;
	}
	else if (CurrentEquipped->Equipment != nullptr)
	{
		Unequip(CurrentEquipped);
		CurrentEquipped->Equipment = Equipment;
		msg = "REPLACING OLD EQUIPMENT";
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, msg);
		return true;
		//TODO take the item out of the inventory
	}
	else { return false; }
}

bool UEquipmentManager::Equip(class ABaseEquipment* Equipment)
{
	// equip it in the right character slot
	switch (Equipment->GetEquippedOn())
	{
	case EEquippedOn::EHead:
		if (HeadArmor->Accepted == EEquippedOn::EHead)
		{
			return CheckEquipped(HeadArmor, Equipment);
		}
		return false;
	case EEquippedOn::EBody:
		if (BodyArmor->Accepted == EEquippedOn::EBody)
		{
			return CheckEquipped(BodyArmor, Equipment);
		}
		return false;
	case EEquippedOn::EHands:
		if (HandArmor->Accepted == EEquippedOn::EHands)
		{
			return CheckEquipped(HandArmor, Equipment);
		}
		return false;
	case EEquippedOn::ELegs:
		if (LegArmor->Accepted == EEquippedOn::ELegs)
		{
			return CheckEquipped(LegArmor, Equipment);
		}
		return false;
	case EEquippedOn::EFeet:
		if (FeetArmor->Accepted == EEquippedOn::EFeet)
		{
			return CheckEquipped(FeetArmor, Equipment);
		}
		return false;
	case EEquippedOn::ERightHand:
		if (RightHand->Accepted == EEquippedOn::ERightHand)
		{
			return CheckEquipped(RightHand, Equipment);
		}
		return false;
	case EEquippedOn::ELeftHand:
		if (LeftHand->Accepted == EEquippedOn::ELeftHand)
		{
			return CheckEquipped(LeftHand, Equipment);
		}
		return false;
	case EEquippedOn::ETwoHanded:
		return CheckEquipped(RightHand, Equipment);
	default:
		return false;
	}
}

void UEquipmentManager::Unequip(struct FEquipment* Current)
{
	//TODO return the item to the inventory
	Current->Equipment = nullptr;
}
