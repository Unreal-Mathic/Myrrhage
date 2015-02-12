// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "MyrrhageGlobals.h"
#include "PaperCharacter.h"
#include "EquipmentManager.h"
#include "StatManager.h"
#include "MyrrhageCharacter.generated.h"

// This class is the default character for Myrrhage, and it is responsible for all
// physical interaction between the player and the world.
//
//   The capsule component (inherited from ACharacter) handles collision with the world
//   The CharacterMovementComponent (inherited from ACharacter) handles movement of the collision capsule
//   The Sprite component (inherited from APaperCharacter) handles the visuals

UCLASS(config=Game)
class AMyrrhageCharacter : public APaperCharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess="true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

protected:
	// The animation to play while running around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Animations)
	class UPaperFlipbook* RunningAnimation;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* IdleAnimation;

	// Picked up items go in the CharacterInventory
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	TArray<ABaseItem*> CharacterInventory;

	// Character armor and weapons equipped
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	UEquipmentManager* CharacterEquipment;

	// Character's innate abilities
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	UStatManager* CharacterStats;

	// Character's innate abilities
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Myrrhage)
	TEnumAsByte<EClass> CharacterClass;

	int num = 0;

	/** Called to choose the correct animation to play based on the character's movement state */
	void UpdateAnimation();

	/** Called for side to side input */
	void MoveRight(float Value);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	virtual void Tick(float DeltaSeconds) override;

	// Inventory methods
	virtual void ReceiveHit(class UPrimitiveComponent*, class AActor*, class UPrimitiveComponent*, bool, FVector, FVector, FVector, const FHitResult&) override;
	
	void PickUpItems(class ABaseItem*);

	void OpenInventory();

	void Equip(class ABaseEquipment*);
	// end of Inventory methods

	// Abilities input
	void Attack();
	void StopAttack();

	void QuickAttack();
	void StopQuickAttack();

	void SlowAttack();
	void StopSlowAttack();


	// end of abilities input

public:
	AMyrrhageCharacter(const FObjectInitializer& ObjectInitializer);

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UStatManager* GetStatManager();
};
