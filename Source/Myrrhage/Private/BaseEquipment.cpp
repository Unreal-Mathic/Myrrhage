// Fill out your copyright notice in the Description page of Project Settings.

#include "MyrrhagePrivate.h"
#include "BaseEquipment.h"

ABaseEquipment::ABaseEquipment(const class FObjectInitializer& PCIP) : Super(PCIP){}

TArray<FStatStruct> ABaseEquipment::GetStats()
{
	return Stats;
}

TEnumAsByte<EEquippedOn> ABaseEquipment::GetEquippedOn()
{
	return EquippedOn;
}

void ABaseEquipment::OnPickUp_Implementation()
{
	Destroy();
}

