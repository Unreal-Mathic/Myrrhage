// Fill out your copyright notice in the Description page of Project Settings.

#include "MyrrhagePrivate.h"
#include "BaseItem.h"

//#if WITH_EDITOR
//bool APaperSpriteActor::GetReferencedContentObjects(TArray<UObject*>& Objects) const
//{
//	if (UPaperSprite* SourceSprite = RenderComponent->GetSprite())
//	{
//		Objects.Add(SourceSprite);
//	}
//	return true;
//}
//#endif

ABaseItem::ABaseItem(const class FObjectInitializer& PCIP) : Super(PCIP){}

void ABaseItem::PickedUp()
{
	OnPickedUp();
}

void ABaseItem::OnPickedUp_Implementation()
{
	// do something
}

FString ABaseItem::GetItemName()
{
	return Name;
}
