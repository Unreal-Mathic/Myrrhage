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

public:
	UAttackManager();
	
	// Attack based on character's equipped weapon
	void Attack(UEquipmentManager*, EAttackType, EClass);

	// Default attacks based on class if no weapon is equipped
	void DefaultBaseAttack(EClass);
	void DefaultWeakAttack(EClass);
	void DefaultStrongAttack(EClass);
	void DefaultUltimateAttack(EClass);
	
protected:
	
};
