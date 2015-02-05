// Fill out your copyright notice in the Description page of Project Settings.

#include "MyrrhagePrivate.h"
#include "Breastplate.h"

ABreastplate::ABreastplate(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	
	
	FStatStruct a = FStatStruct();
	FStatStruct b = FStatStruct();
	FStatStruct c = FStatStruct();

	a.SetType(EStat::EMight);
	a.SetValue((rand() % 10) + 1);

	b.SetType(EStat::EPresence);
	b.SetValue((rand() % 10) + 1);

	c.SetType(EStat::EResistance);
	c.SetValue((rand() % 10) + 1);

	m_Stats.Add(a);
	m_Stats.Add(b);
	m_Stats.Add(c);
	m_Name = FString(TEXT("BAKA"));
}


