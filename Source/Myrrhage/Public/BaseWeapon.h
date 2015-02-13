// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseEquipment.h"
#include "BaseWeapon.generated.h"

/**
 * 
 */
UCLASS(abstract)
class MYRRHAGE_API ABaseWeapon : public ABaseEquipment
{
	GENERATED_BODY()
public:
	ABaseWeapon(const class FObjectInitializer& PCIP);

	// The attacks of the weapon get called in AttackManager
	void BaseAttack();
	void WeakAttack();
	void StrongAttack();
	void UltimateAttack();
};
