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
	/** Called form a notify when the attack animation has ended */
	UFUNCTION(BlueprintCallable, Category = "Game Combat")
	void StartDoingDamage();

	/** Called form a notify when the attack animation has ended */
	UFUNCTION(BlueprintCallable, Category = "Game Combat")
	void StopDoingDamage();

	/** Responsible for creating the collision box */
	UFUNCTION()
	void AttackTrace();

	/** Should the character be doing damage at the moment? */
	bool bDoingDamage;

	void ProcessHitActor(AActor*);

	/** list of actors currently being hit */
	TArray<AActor*> HitActors;

public:
	UAttackManager();
	void Attack(UEquipmentManager*, TEnumAsByte<EAttackType>, TEnumAsByte<EClass>);
	void DefaultBaseAttack(TEnumAsByte<EClass>);
	void DefaultWeakAttack(TEnumAsByte<EClass>);
	void DefaultStrongAttack(TEnumAsByte<EClass>);
	void DefaultUltimateAttack(TEnumAsByte<EClass>);
};
