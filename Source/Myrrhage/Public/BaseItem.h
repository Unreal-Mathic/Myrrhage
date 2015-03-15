// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyrrhageGlobals.h"
#include "PaperSpriteActor.h"
#include "BaseItem.generated.h"

/**
 * 
 */
UCLASS(abstract)
class MYRRHAGE_API ABaseItem : public APaperSpriteActor
{
	GENERATED_BODY()

public:
	ABaseItem(const class FObjectInitializer& PCIP);

	UFUNCTION(BlueprintCallable, Category = Item)
	virtual void PickedUp();

	// The item can be picked up
	UFUNCTION(BlueprintNativeEvent)
	void OnPickedUp();

	virtual void OnPickedUp_Implementation();

	// Getter for Name
	FString GetItemName();

protected:
	// The item can be a weapon, armor or potion
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	EItem ItemType;

	// All items must have a name
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	FString Name;
};
