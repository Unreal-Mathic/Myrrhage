// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "MyrrhageGlobals.h"
#include "PaperCharacter.h"
#include "EquipmentManager.h"
#include "StatManager.h"
#include "AttackManager.h"
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

public:
	AMyrrhageCharacter(const FObjectInitializer& ObjectInitializer);

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	// Getter for StatManager
	UStatManager* GetStatManager();

	// Getter for CharacterHealth
	float GetCharacterHealth() const;

protected:
	// The animation to play while running around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Animations)
	class UPaperFlipbook* RunningAnimation;

	// The animation to play while walking around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* WalkingAnimation;

	// The animation to play while jumping around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* JumpingAnimation;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* IdleAnimation;

	// The animation to play while doing a base attack (Q)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* BaseAttackAnimation;

	// The animation to play while doing a weak attack (W)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* WeakAttackAnimation;

	// The animation to play while doing a strong attack (E)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* StrongAttackAnimation;

	// The animation to play while doing ultimate attack (R)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* UltimateAttackAnimation;

	// The animation to play while doing a range attack (TODO throwing or shooting weapons + projectiles)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* RangeAttackAnimation;

	// Picked up items go in the CharacterInventory
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	TArray<ABaseItem*> CharacterInventory;

	// Character armor and weapons equipped
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	UEquipmentManager* CharacterEquipment;

	// Character's innate abilities
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	UStatManager* CharacterStats;

	// Character's attack manager
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myrrhage)
	UAttackManager* CharacterAttacks;

	// Character's class type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Myrrhage)
	EClass CharacterClass;

	// Character's preferred hand (or ambidextrous)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Myrrhage)
	EHandedness CharacterHandedness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Myrrhage)
	float CharacterHealth;

	int num = 0;

	/** Called to choose the correct animation to play based on the character's movement state */
	void UpdateAnimation();

	/** Called for side to side input */
	void MoveRight(float Value);

	bool bIsRunning;

	/** Called for running input */
	void Running();
	void StopRunning();

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	// Override Tick funtion
	virtual void Tick(float DeltaSeconds) override;

	// Inventory methods
	virtual void ReceiveHit(class UPrimitiveComponent*, class AActor*, class UPrimitiveComponent*, bool, FVector, FVector, FVector, const FHitResult&) override;
	
	void PickUpItems(class ABaseItem*);

	void OpenInventory();

	void Equip();
	// end of Inventory methods

	// Abilities input

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

	bool bIsAttacking;

	void PlayAnimationOnce(UPaperFlipbook*);

	void BaseAttack();

	void WeakAttack();

	void StrongAttack();

	void UltimateAttack();

	void StopAttack();
	// end of abilities input

	bool bIsJumping;
	virtual void Jump() override;
	virtual void StopJumping() override;
};

FORCEINLINE float AMyrrhageCharacter::GetCharacterHealth() const
{
	return CharacterHealth;
}
