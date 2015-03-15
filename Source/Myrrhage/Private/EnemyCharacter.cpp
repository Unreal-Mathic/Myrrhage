// Fill out your copyright notice in the Description page of Project Settings.

#include "MyrrhagePrivate.h"
#include "EnemyCharacter.h"
#include "PaperFlipbookComponent.h"

AEnemyCharacter::AEnemyCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Setup the assets
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> WalkingAnimationAsset;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> ShootingAnimationAsset;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> DyingAnimationAsset;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> IdleAnimationAsset;
		FConstructorStatics()
			: WalkingAnimationAsset(TEXT("/Game/Sprites/EnemyWalking.EnemyWalking"))
			, ShootingAnimationAsset(TEXT("/Game/Sprites/EnemyShoot.EnemyShoot"))
			, DyingAnimationAsset(TEXT("/Game/Sprites/EnemyDying.EnemyDying"))
			, IdleAnimationAsset(TEXT("/Game/Sprites/EnemyIdle.EnemyIdle"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	SetActorEnableCollision(true);

	WalkingAnimation = ConstructorStatics.WalkingAnimationAsset.Get();
	ShootingAnimation = ConstructorStatics.ShootingAnimationAsset.Get();
	DyingAnimation = ConstructorStatics.DyingAnimationAsset.Get();
	IdleAnimation = ConstructorStatics.IdleAnimationAsset.Get();
	GetSprite()->SetFlipbook(IdleAnimation);
	DetectionSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("DetectionSphere"));
	AttackSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("AttackSphere"));
	CreateDetectionSphere(500.0f);
	CreateAttackSphere(250.0f);
}

void AEnemyCharacter::CreateDetectionSphere(float radius)
{
	//Create player detection sphere
	DetectionSphere->AttachTo(RootComponent);
	DetectionSphere->SetSphereRadius(radius);
}

void AEnemyCharacter::CreateAttackSphere(float radius)
{
	//Create player attack sphere
	AttackSphere->AttachTo(RootComponent);
	AttackSphere->SetSphereRadius(radius);
}

// Try and face the player if the player is seen
void AEnemyCharacter::FacePlayer()
{
	//AMyrrhageCharacter* Player;
}

void AEnemyCharacter::AttackTrace()
{
	TArray<struct FOverlapResult> OutOverlaps;
	FQuat Rotation = GetTransform().GetRotation();
	FVector Start = GetTransform().GetLocation() + Rotation.Rotator().Vector() * 100.0f;
	FCollisionShape CollisionHitShape;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	FCollisionObjectQueryParams CollisionObjectTypes;
	CollisionObjectTypes.AddObjectTypesToQuery(ECollisionChannel::ECC_PhysicsBody);
	CollisionObjectTypes.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
	CollisionObjectTypes.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);

	CollisionHitShape = FCollisionShape::MakeBox(FVector(200.0f, 60.0f, 0.5f));
	GetWorld()->OverlapMulti(OutOverlaps, Start, Rotation, CollisionHitShape, CollisionParams, CollisionObjectTypes);
	UpdateAnimation();

	for (int i = 0; i < OutOverlaps.Num(); ++i)
	{
		AMyrrhageCharacter* Player = dynamic_cast<AMyrrhageCharacter*>(OutOverlaps[i].GetActor());
		if (Player && !HitActors.Contains(Player))
		{
			ProcessMove(OutOverlaps[i].GetActor());
		}
	}
}

void AEnemyCharacter::SetCurrentState(EEnemyState NewState)
{
	CurrentState = NewState;

	HandleNewState(NewState);
}

void AEnemyCharacter::HandleNewState(EEnemyState NewState)
{
	switch (NewState)
	{
	case EEnemyState::EIdle:

		break;
	case EEnemyState::EMoving:
	
		break;
	case EEnemyState::EAttacking:
		
		break;
	case EEnemyState::ERetreating:

		break;
	case EEnemyState::EUnknown:
	default:
		//do nothing
		break;

	}
}

void AEnemyCharacter::ProcessAttack(AActor* ActorToProcess)
{

}

void AEnemyCharacter::MoveTrace()
{
	//Get all overlapping Actors and store them in a CollectedActors array
	TArray<AActor*> CollectedActors;
	DetectionSphere->GetOverlappingActors(CollectedActors);

	for (int i = 0; i < CollectedActors.Num(); ++i)
	{
		AMyrrhageCharacter* Player = dynamic_cast<AMyrrhageCharacter*>(CollectedActors[i]);
		if (Player && !PlayerActors.Contains(Player))
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, "Actor added");
			ProcessMove(Player);
		}
	}
}

// Enemy moves toward character to get to shooting range
// Enemy moves away from character to get to optimum shooting range
// Enemy moves away from character if low on health
// Enemy shoot at character if at optimum shooting range
void AEnemyCharacter::ProcessMove(AActor* ActorToProcess)
{
	/*if (!ActorToProcess || PlayerActors.Contains(ActorToProcess))
	{
		return;
	}
	PlayerActors.AddUnique(ActorToProcess);*/
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), -1.0f);
}

void AEnemyCharacter::UpdateAnimation()
{
	const FVector EnemyVelocity = GetVelocity();
	const float EnemySpeed = EnemyVelocity.Size();
	
	// Are we moving or standing still?
	UPaperFlipbook* DesiredAnimation = (EnemySpeed > 0.0f) ? WalkingAnimation : IdleAnimation;

	GetSprite()->SetFlipbook(DesiredAnimation);
}

void AEnemyCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	MoveTrace();
}
