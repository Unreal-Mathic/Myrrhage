// Fill out your copyright notice in the Description page of Project Settings.

#include "MyrrhagePrivate.h"
#include "Tunic.h"

ATunic::ATunic(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	FStatStruct a = FStatStruct();
	FStatStruct b = FStatStruct();
	FStatStruct c = FStatStruct();
	
	a.SetType(EStat::EMight);
	a.SetValue((rand() % 5) + 1);

	b.SetType(EStat::EKnowledge);
	b.SetValue((rand() % 10) + 1);

	c.SetType(EStat::EResistance);
	c.SetValue((rand() % 10) + 1);

	Stats.Add(a);
	Stats.Add(b);
	Stats.Add(c);

	EquippedOn = EEquippedOn::EBody;
	ClassType = EClass::EHacker;

	RequiredStat = FStatStruct();
	RequiredStat.SetType(EStat::EKnowledge);
	RequiredStat.SetValue(8.0f);

	Name = FString(TEXT("SHIMATA"));
}


