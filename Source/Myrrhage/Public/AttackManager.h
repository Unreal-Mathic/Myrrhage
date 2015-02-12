// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyrrhageGlobals.h"
#include "EquipmentManager.h"

#include "Object.h"
#include "AttackManager.generated.h"

/**
 * Deals with player attacks, and sets the default attacks of each class
 */
UCLASS()
class MYRRHAGE_API UAttackManager : public UObject
{
	GENERATED_BODY()
	
protected:


public:
	void Attack(UEquipmentManager*, TEnumAsByte<EAttackType>, TEnumAsByte<EClass>);
	void DefaultBaseAttack(TEnumAsByte<EClass>);
	void DefaultWeakAttack(TEnumAsByte<EClass>);
	void DefaultStrongAttack(TEnumAsByte<EClass>);
	void DefaultUltimateAttack(TEnumAsByte<EClass>);
};
