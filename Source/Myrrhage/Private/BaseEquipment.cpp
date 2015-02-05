// Fill out your copyright notice in the Description page of Project Settings.

#include "MyrrhagePrivate.h"
#include "BaseEquipment.h"

void ABaseEquipment::OnPickUp_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "I'VE BEEN PICKED UP");
	Destroy();
}

