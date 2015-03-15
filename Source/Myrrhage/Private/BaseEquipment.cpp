// Fill out your copyright notice in the Description page of Project Settings.

#include "MyrrhagePrivate.h"
#include "BaseEquipment.h"

ABaseEquipment::ABaseEquipment(const class FObjectInitializer& PCIP) : Super(PCIP){}

TArray<FStatStruct> ABaseEquipment::GetStats()
{
	return Stats;
}

FStatStruct ABaseEquipment::GetRequiredStat()
{
	return RequiredStat;
}

void ABaseEquipment::SetEquippedOn(EEquippedOn EquippedOn)
{
	this->EquippedOn = EquippedOn;
}

EEquippedOn ABaseEquipment::GetEquippedOn()
{
	return EquippedOn;
}

EClass ABaseEquipment::GetClassType()
{
	return ClassType;
}

void ABaseEquipment::PickedUp()
{
	// Do Custom Stuff here
	// Call Super::PickedUp()
	// Or do custom stuff here
	// Or forget Super and just call OnPickedUp() it's protected after all

	OnPickedUp();
}

void ABaseEquipment::OnPickedUp_Implementation()
{
	Destroy();
}

