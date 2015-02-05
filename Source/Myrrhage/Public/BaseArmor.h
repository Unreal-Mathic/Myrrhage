// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseEquipment.h"
#include "BaseArmor.generated.h"

/**
*
*/
UCLASS(abstract)
class MYRRHAGE_API ABaseArmor : public ABaseEquipment
{
	GENERATED_BODY()

public:
	ABaseArmor(const class FObjectInitializer& PCIP);

};
