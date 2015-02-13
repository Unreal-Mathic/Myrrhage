// Fill out your copyright notice in the Description page of Project Settings.

#include "MyrrhagePrivate.h"
#include "AttackManager.h"

UAttackManager::UAttackManager()
{
	// Character Attack
	/*TArray<struct FOverlapResult> OutOverlaps;
	FQuat Rotation = GetTransform().GetRotation();
	FVector Start = GetTransform().GetLocation() + Rotation.Rotator().Vector() * 100.0f;
	FCollisionShape CollisionHitShape;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	FCollisionObjectQueryParams CollisionObjectTypes;
	CollisionObjectTypes.AddObjectTypesToQuery(ECollisionChannel::ECC_PhysicsBody);
	CollisionObjectTypes.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
	CollisionObjectTypes.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);

	CollisionHitShape = FCollisionShape::MakeBox(FVector(100.0f, 60.0f, 0.5f));
	GetWorld()->OverlapMulti(OutOverlaps, Start, Rotation, CollisionHitShape, CollisionParams, CollisionObjectTypes);

	for (int i = 0; i < OutOverlaps.Num(); ++i)
	{
		if (OutOverlaps[i].GetActor() && !HitActors.Contains(OutOverlaps[i].GetActor()))
		{
			ProcessHitActor(OutOverlaps[i].GetActor());
		}
	}*/
}

void UAttackManager::StartDoingDamage()
{
	bDoingDamage = true;
}

void UAttackManager::StopDoingDamage()
{
	bDoingDamage = false;
	//Clear Hit Actors array
	HitActors.Empty();
}

void UAttackManager::AttackTrace()
{

}

void UAttackManager::ProcessHitActor(AActor* ActorToProcess)
{
	//if (!ActorToProcess || HitActors.Contains(ActorToProcess))
	//{
	//	return;
	//}
	////Add this actor to the array because we are spawning one box per tick and we don't want to hit the same actor twice during the same attack animation
	//HitActors.AddUnique(ActorToProcess);
	//FHitResult AttackHitResult;
	//FDamageEvent AttackDamageEvent;
	//AMyrrhageCharacter* GameCharacter = Cast<AMyrrhageCharacter>(ActorToProcess);

	//if (GameCharacter)
	//{
	//	//Deal damage to the character
	//	ActorToProcess->TakeDamage(50.0f, AttackDamageEvent, GetController(), this);
	//}
}

void UAttackManager::Attack(UEquipmentManager* Equipment, TEnumAsByte<EAttackType> AttackType, TEnumAsByte<EClass> Class)
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

void UAttackManager::DefaultBaseAttack(TEnumAsByte<EClass> Class)
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

void UAttackManager::DefaultWeakAttack(TEnumAsByte<EClass> Class)
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

void UAttackManager::DefaultStrongAttack(TEnumAsByte<EClass> Class)
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

void UAttackManager::DefaultUltimateAttack(TEnumAsByte<EClass> Class)
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
