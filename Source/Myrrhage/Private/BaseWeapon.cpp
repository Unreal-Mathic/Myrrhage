// Fill out your copyright notice in the Description page of Project Settings.

#include "MyrrhagePrivate.h"
#include "BaseWeapon.h"

ABaseWeapon::ABaseWeapon(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	ItemType = EItem::EWeapon;
}

void ABaseWeapon::BaseAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, "BaseAttack");
}

void ABaseWeapon::WeakAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, "WeakAttack");
}

void ABaseWeapon::StrongAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, "StrongAttack");
}

void ABaseWeapon::UltimateAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, "UltimateAttack");
}
