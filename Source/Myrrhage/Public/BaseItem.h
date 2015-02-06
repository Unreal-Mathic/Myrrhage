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

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	TEnumAsByte<EItem> ItemType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	FString Name;

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnPickUp();

	ABaseItem(const class FObjectInitializer& PCIP);

	FString GetItemName();
};
