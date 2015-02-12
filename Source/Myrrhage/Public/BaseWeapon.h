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
	
protected:
	ABaseWeapon(const class FObjectInitializer& PCIP);

public:
	void BaseAttack();
	void WeakAttack();
	void StrongAttack();
	void UltimateAttack();
};
