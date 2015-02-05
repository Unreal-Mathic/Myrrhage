// Fill out your copyright notice in the Description page of Project Settings.

#include "MyrrhagePrivate.h"
#include "BaseArmor.h"

ABaseArmor::ABaseArmor(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	m_ItemType = EItem::EArmor;
}
