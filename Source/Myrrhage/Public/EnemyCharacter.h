// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperCharacter.h"
#include "MyrrhageCharacter.h"
#include "EnemyCharacter.generated.h"

enum class EEnemyState : short
{
	EIdle,
	EMoving,
	EAttacking,
	ERetreating,
	EUnknown
};

/**
 * 
 */
UCLASS()
class MYRRHAGE_API AEnemyCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter(const FObjectInitializer& ObjectInitilizer);

	/** Detection range */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Power)
	class USphereComponent* DetectionSphere;

	/** Attack range */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Power)
	class USphereComponent* AttackSphere;

	void CreateDetectionSphere(float radius);

	void CreateAttackSphere(float radius);

#pragma region State functions
	EEnemyState CurrentState;

	void HandleNewState(EEnemyState NewState);

	void SetCurrentState(EEnemyState NewState);

	EEnemyState GetCurrentState() const;
#pragma endregion
protected:
	// The animation to play while walking around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* WalkingAnimation;

	// The animation to play while shooting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* ShootingAnimation;

	// The animation to play while dying
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* DyingAnimation;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* IdleAnimation;

	bool bIsMoving;

private:
	void FacePlayer();

	void AttackTrace();
	void ProcessAttack(AActor* ActorToProcess);

	void MoveTrace();

	void ProcessMove(AActor* ActorToProcess);
	
	void UpdateAnimation();

	// Override Tick funtion
	virtual void Tick(float DeltaSeconds) override;

	/** list of actors currently being hit */
	TArray<AActor*> HitActors;

	// list of actors
	TArray<AActor*> PlayerActors;
};

FORCEINLINE EEnemyState AEnemyCharacter::GetCurrentState() const
{
	return CurrentState;
}