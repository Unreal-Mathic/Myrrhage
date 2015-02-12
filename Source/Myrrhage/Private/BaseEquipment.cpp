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

TEnumAsByte<EEquippedOn> ABaseEquipment::GetEquippedOn()
{
	return EquippedOn;
}

TEnumAsByte<EClass> ABaseEquipment::GetClassType()
{
	return ClassType;
}

void ABaseEquipment::OnPickUp_Implementation()
{
	Destroy();
}

