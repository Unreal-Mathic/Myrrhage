// Fill out your copyright notice in the Description page of Project Settings.

#include "MyrrhagePrivate.h"
#include "BaseWeapon.h"

ABaseWeapon::ABaseWeapon(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	ItemType = EItem::EWeapon;
}
