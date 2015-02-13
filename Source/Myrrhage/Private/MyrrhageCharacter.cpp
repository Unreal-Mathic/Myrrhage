// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MyrrhagePrivate.h"
#include "MyrrhageCharacter.h"
#include "BaseItem.h"
#include "BaseEquipment.h"
#include "PaperFlipbookComponent.h"

//////////////////////////////////////////////////////////////////////////
// AMyrrhageCharacter

AMyrrhageCharacter::AMyrrhageCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Setup the assets
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> RunningAnimationAsset;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> WalkingAnimationAsset;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> JumpingAnimationAsset;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> IdleAnimationAsset;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> BaseAttackAnimationAsset;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> WeakAttackAnimationAsset;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> StrongAttackAnimationAsset;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> UltimateAttackAnimationAsset;
		//ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> RangeAttackAnimationAsset;
		FConstructorStatics()
			: RunningAnimationAsset(TEXT("/Game/Sprites/RunningAnimation.RunningAnimation"))
			, WalkingAnimationAsset(TEXT("/Game/Sprites/WalkingAnimation.WalkingAnimation"))
			, JumpingAnimationAsset(TEXT("/Game/Sprites/JumpingAnimation.JumpingAnimation"))
			, IdleAnimationAsset(TEXT("/Game/Sprites/IdleAnimation.IdleAnimation"))
			, BaseAttackAnimationAsset(TEXT("/Game/Sprites/BaseAttackAnimation.BaseAttackAnimation"))
			, WeakAttackAnimationAsset(TEXT("/Game/Sprites/WeakAttackAnimation.WeakAttackAnimation"))
			, StrongAttackAnimationAsset(TEXT("/Game/Sprites/StrongAttackAnimation.StrongAttackAnimation"))
			, UltimateAttackAnimationAsset(TEXT("/Game/Sprites/UltimateAttackAnimation.UltimateAttackAnimation"))
			//, RangeAttackAnimationAsset(TEXT("/Game/Sprites/FinnRange.FinnRange"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	SetActorEnableCollision(true);

	RunningAnimation = ConstructorStatics.RunningAnimationAsset.Get();
	WalkingAnimation = ConstructorStatics.WalkingAnimationAsset.Get();
	JumpingAnimation = ConstructorStatics.JumpingAnimationAsset.Get();
	IdleAnimation = ConstructorStatics.IdleAnimationAsset.Get();
	BaseAttackAnimation = ConstructorStatics.BaseAttackAnimationAsset.Get();
	WeakAttackAnimation = ConstructorStatics.WeakAttackAnimationAsset.Get();
	StrongAttackAnimation = ConstructorStatics.StrongAttackAnimationAsset.Get();
	UltimateAttackAnimation = ConstructorStatics.UltimateAttackAnimationAsset.Get();
	//RangeAttackAnimation = ConstructorStatics.RangeAttackAnimationAsset.Get();
	GetSprite()->SetFlipbook(IdleAnimation);

	// Use only Yaw from the controller and ignore the rest of the rotation.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Set the size of our collision capsule.
	GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f);
	GetCapsuleComponent()->SetCapsuleRadius(40.0f);

	// Create a camera boom attached to the root (capsule)
	CameraBoom = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 75.0f);
	CameraBoom->bAbsoluteRotation = true;
	CameraBoom->RelativeRotation = FRotator(0.0f, -90.0f, 0.0f);

	// Create an orthographic camera (no perspective) and attach it to the boom
	SideViewCameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("SideViewCamera"));
	SideViewCameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	SideViewCameraComponent->OrthoWidth = 2048.0f;
	SideViewCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);

	// Prevent all automatic rotation behavior on the camera, character, and camera component
	CameraBoom->bAbsoluteRotation = true;
	SideViewCameraComponent->bUsePawnControlRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	// Configure character movement
	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.0f;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxFlySpeed = 600.0f;

	// Lock character motion onto the XZ plane, so the character can't move in or out of the screen
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

	// Behave like a traditional 2D platformer character, with a flat bottom instead of a curved capsule bottom
	// Note: This can cause a little floating when going up inclines; you can choose the tradeoff between better
	// behavior on the edge of a ledge versus inclines by setting this to true or false
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

	// Enable replication on the Sprite component so animations show up when networked
	GetSprite()->SetIsReplicated(true);
	bReplicates = true;
	
	CharacterEquipment = NewObject<UEquipmentManager>();
	CharacterStats = NewObject<UStatManager>();
	CharacterAttacks = NewObject<UAttackManager>();
	CharacterClass = EClass::EHacker;
	CharacterHandedness = EHandedness::ELeftHanded;
}

//////////////////////////////////////////////////////////////////////////
// Animation

void AMyrrhageCharacter::UpdateAnimation()
{
	if (bIsAttacking || bIsJumping)
		return;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, "NotAttacking");
	const FVector PlayerVelocity = GetVelocity();
	const float PlayerSpeed = PlayerVelocity.Size();

	if (bIsRunning && PlayerSpeed > 0.0f)
	{
		GetSprite()->SetFlipbook(RunningAnimation);
	}
	else
	{
		// Are we moving or standing still?
		UPaperFlipbook* DesiredAnimation = (PlayerSpeed > 0.0f) ? WalkingAnimation : IdleAnimation;

		GetSprite()->SetFlipbook(DesiredAnimation);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMyrrhageCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// Note: the 'Jump' action and the 'MoveRight' axis are bound to actual keys/buttons/sticks in DefaultInput.ini (editable from Project Settings..Input)
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMyrrhageCharacter::Jump);
	InputComponent->BindAxis("MoveRight", this, &AMyrrhageCharacter::MoveRight);

	// Running
	InputComponent->BindAction("Shift", IE_Pressed, this, &AMyrrhageCharacter::Running);
	InputComponent->BindAction("Shift", IE_Released, this, &AMyrrhageCharacter::StopRunning);

	InputComponent->BindAction("Inventory", IE_Pressed, this, &AMyrrhageCharacter::OpenInventory);

	// Debugging purposes
	InputComponent->BindAction("Equip", IE_Pressed, this, &AMyrrhageCharacter::Equip);

	// Input for character attacking
	InputComponent->BindAction("Attack1", IE_Pressed, this, &AMyrrhageCharacter::BaseAttack);
	InputComponent->BindAction("Attack2", IE_Pressed, this, &AMyrrhageCharacter::WeakAttack);
	InputComponent->BindAction("Attack3", IE_Pressed, this, &AMyrrhageCharacter::StrongAttack);
	InputComponent->BindAction("Attack4", IE_Pressed, this, &AMyrrhageCharacter::UltimateAttack);

	InputComponent->BindTouch(IE_Pressed, this, &AMyrrhageCharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &AMyrrhageCharacter::TouchStopped);
}

void AMyrrhageCharacter::MoveRight(float Value)
{
	// Update animation to match the motion
	UpdateAnimation();

	// Set the rotation so that the character faces his direction of travel.
	if (Controller != nullptr)
	{
		if (Value < 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0, 180.0f, 0.0f));
		}
		else if (Value > 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}

	// Apply the input to the character motion
	if (bIsRunning)
		AddMovementInput(FVector(3.0f, 0.0f, 0.0f), Value);
	else
		AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}

void AMyrrhageCharacter::Jump()
{
	Super::Jump();
	if (!bIsJumping)
	{
		bIsJumping = true;
		GetSprite()->SetFlipbook(JumpingAnimation);
		GetWorldTimerManager().SetTimer(this, &AMyrrhageCharacter::StopJumping, JumpingAnimation->GetTotalDuration(), true, JumpingAnimation->GetTotalDuration());
	}
}

void AMyrrhageCharacter::StopJumping()
{
	Super::StopJumping();
	bIsJumping = false;
}

void AMyrrhageCharacter::Running()
{
	bIsRunning = true;
}

void AMyrrhageCharacter::StopRunning()
{
	bIsRunning = false;
}

void AMyrrhageCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// run when shift is held down
	Running();
	// jump on any touch
	Jump();
	// attacks
	BaseAttack();
	WeakAttack();
	StrongAttack();
	UltimateAttack();
}

void AMyrrhageCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopRunning();
}

void AMyrrhageCharacter::OpenInventory()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Inventory GUI not implemented yet.");
}

//////////////////////////////////////////////////////////////////////////
// Player input attacks

void AMyrrhageCharacter::ExecuteAnimation(UPaperFlipbook* Animation)
{
	if (!bIsAttacking)
	{
		bIsAttacking = true;
		GetSprite()->SetFlipbook(Animation);
		GetWorldTimerManager().SetTimer(this, &AMyrrhageCharacter::StopAttack, Animation->GetTotalDuration(), false, Animation->GetTotalDuration());
		CharacterAttacks->Attack(CharacterEquipment, EAttackType::EBaseAttack, CharacterClass);
	}
}

void AMyrrhageCharacter::BaseAttack()
{
	ExecuteAnimation(BaseAttackAnimation);
}

void AMyrrhageCharacter::WeakAttack()
{
	ExecuteAnimation(WeakAttackAnimation);
}

void AMyrrhageCharacter::StrongAttack()
{
	if (bIsJumping)
		ExecuteAnimation(StrongAttackAnimation);
}

void AMyrrhageCharacter::UltimateAttack()
{
	ExecuteAnimation(UltimateAttackAnimation);
}

void AMyrrhageCharacter::StopAttack()
{
	bIsAttacking = false;
}

//////////////////////////////////////////////////////////////////////////
// Player stats/equipment

UStatManager* AMyrrhageCharacter::GetStatManager()
{
	return CharacterStats;
}

void AMyrrhageCharacter::Equip()
{
	// TODO implement with GUI or HUD and put in Equip() method
	if (CharacterInventory.Num() <= 0)
		return;
	// get the first item in the inventory and try to equip it
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, CharacterStats->GetCharacterStats());
	if (dynamic_cast<ABaseEquipment*>(CharacterInventory[num]))
	{
		ABaseEquipment* Equip = dynamic_cast<ABaseEquipment*>(CharacterInventory[num]);
		if (CharacterClass == Equip->GetClassType())
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Equip->GetItemName());
			CharacterEquipment->Equip(CharacterStats, Equip, CharacterHandedness);
		}

		num++;
		if (num >= CharacterInventory.Num()){ num = 0; }
	}
	else
	{
		bIsJumping = false;
	}
}

//////////////////////////////////////////////////////////////////////////
// Interaction with world

void AMyrrhageCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMyrrhageCharacter::ReceiveHit(class UPrimitiveComponent* MyComp,
	class AActor* Other,
	class UPrimitiveComponent* OtherComp,
	bool bSelfMoved,
	FVector HitLocation,
	FVector HitNormal,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	Super::ReceiveHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	if (dynamic_cast<ABaseItem*>(Other))
	{
		PickUpItems(dynamic_cast<ABaseItem*>(Other));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, Other->GetName());
	}
}

void AMyrrhageCharacter::PickUpItems(class ABaseItem* Item)
{
	CharacterInventory.Add(Item);
	if (dynamic_cast<ABaseEquipment*>(Item))
	{
		dynamic_cast<ABaseEquipment*>(Item)->OnPickUp_Implementation();
	}
#ifdef UE_BUILD_DEBUG
	ABaseItem* CurItem = NULL;
	for (int32 b = 0; b < CharacterInventory.Num(); b++)
	{
		CurItem = CharacterInventory[b];
		if (!CurItem) continue;
		if (!CurItem->IsValidLowLevel()) continue;
	}
#endif
}
