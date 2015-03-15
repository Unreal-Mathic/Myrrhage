// Fill out your copyright notice in the Description page of Project Settings.

#include "MyrrhagePrivate.h"
#include "AttackManager.h"

UAttackManager::UAttackManager()
{
	
}

void UAttackManager::Attack(UEquipmentManager* Equipment, EAttackType AttackType, EClass Class)
{
	switch (AttackType)
	{
	case EAttackType::EBaseAttack:
		if (Equipment->HasWeapon())
			Equipment->GetWeapon()->BaseAttack();
		else
			DefaultBaseAttack(Class);
		break;
	case EAttackType::EWeakAttack:
		if (Equipment->HasWeapon())
			Equipment->GetWeapon()->WeakAttack();
		else
			DefaultWeakAttack(Class);
		break;
	case EAttackType::EStrongAttack:
		if (Equipment->HasWeapon())
			Equipment->GetWeapon()->StrongAttack();
		else
			DefaultStrongAttack(Class);
		break;
	case EAttackType::EUltimateAttack:
		if (Equipment->HasWeapon())
			Equipment->GetWeapon()->UltimateAttack();
		else
			DefaultUltimateAttack(Class);
		break;
	case EAttackType::EUnknown:
	default:
		break;
	}
}

void UAttackManager::DefaultBaseAttack(EClass Class)
{
	FString msg = "DefaultBaseAttack ";
	switch (Class)
	{
	case EClass::ECyborg:
		msg += "Cyborg";
		break;
	case EClass::EInfantry:
		msg += "Infantry";
		break;
	case EClass::EHacker:
		msg += "Hacker";
		break;
	case EClass::EPsion:
		msg += "Psion";
		break;
	case EClass::EUnknown:
	default:
		break;
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, msg);
}

void UAttackManager::DefaultWeakAttack(EClass Class)
{
	FString msg = "DefaultWeakAttack ";
	switch (Class)
	{
	case EClass::ECyborg:
		msg += "Cyborg";
		break;
	case EClass::EInfantry:
		msg += "Infantry";
		break;
	case EClass::EHacker:
		msg += "Hacker";
		break;
	case EClass::EPsion:
		msg += "Psion";
		break;
	case EClass::EUnknown:
	default:
		break;
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, msg);
}

void UAttackManager::DefaultStrongAttack(EClass Class)
{
	FString msg = "DefaultStrongAttack ";
	switch (Class)
	{
	case EClass::ECyborg:
		msg += "Cyborg";
		break;
	case EClass::EInfantry:
		msg += "Infantry";
		break;
	case EClass::EHacker:
		msg += "Hacker";
		break;
	case EClass::EPsion:
		msg += "Psion";
		break;
	case EClass::EUnknown:
	default:
		break;
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, msg);
}

void UAttackManager::DefaultUltimateAttack(EClass Class)
{
	FString msg = "DefaultUltimateAttack ";
	switch (Class)
	{
	case EClass::ECyborg:
		msg += "Cyborg";
		break;
	case EClass::EInfantry:
		msg += "Infantry";
		break;
	case EClass::EHacker:
		msg += "Hacker";
		break;
	case EClass::EPsion:
		msg += "Psion";
		break;
	case EClass::EUnknown:
	default:
		break;
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, msg);
}

//void UAttackManager::Tick(float DeltaSeconds)
//{
//	Super::Tick(DeltaSeconds);
//
//	if (bDoingDamage)
//	{
//		//We will be c
//		AttackTrace();
//	}
//}
