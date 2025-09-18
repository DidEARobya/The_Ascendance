// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerMovementComponent.generated.h"

UENUM(BlueprintType)
enum ECustomMovementMode
{
	CMOVE_NONE UMETA(DisplayName = "None"),

	CMOVE_SPRINTING UMETA(DisplayName = "Sprinting"),
	CMOVE_CROUCHING UMETA(DisplayName = "Crouching"),
	CMOVE_CROUCH_SPRINTING UMETA(DisplayName = "Crouch Sprinting"),

	CMOVE_MAX UMETA(Hidden),
};

class APlayerCharacter;

UCLASS()
class THEASCENDANCE_API UPlayerMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	virtual void UpdateCharacterStateBeforeMovement(float deltaSeconds) override;
	virtual void UpdateCharacterStateAfterMovement(float deltaSeconds) override;

	void TrySprinting();
	bool CanSprint();
	void PhysSprinting(float deltaTime, int32 iterations);

	void TryCrouching();
	bool CanCrouch();
	void PhysCrouching(float deltaTime, int32 iterations);
	bool CanUnCrouch();

	UFUNCTION(BlueprintPure)
	float GetSpeed();
	UFUNCTION(BlueprintPure)
	bool IsWalkingCustom();
	UFUNCTION(BlueprintPure)
	bool IsSprinting();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsCrouchingCustom();
	bool IsCustomMovementMode();
	float GetCapsuleRadius();
	float GetCapsuleHalfHeight();
	virtual float GetMaxSpeed() const override;

protected:
	virtual void InitializeComponent() override;
	virtual void PhysCustom(float deltaTime, int32 iterations) override;

private:
	//---- MANTLING ----  Currently Unused
	//UPROPERTY(EditDefaultsOnly, Category = "Player Movement | Mantle", meta = (DisplayName = "Mantle Forward Reach"))
	//float m_MaxFrontMantleCheckDistance = 50;
	//UPROPERTY(EditDefaultsOnly, Category = "Player Movement | Mantle")
	//float m_MantleHeightOffsetDistance = 30;
	//UPROPERTY(EditDefaultsOnly, Category = "Player Movement | Mantle")
	//float m_MantleReachHeight = 50;
	//UPROPERTY(EditDefaultsOnly, Category = "Player Movement | Mantle")
	//float m_MantleMinWallSteepnessAngle = 75;
	//UPROPERTY(EditDefaultsOnly, Category = "Player Movement | Mantle")
	//float m_MantleMaxSurfaceAngle = 40;
	//UPROPERTY(EditDefaultsOnly, Category = "Player Movement | Mantle")
	//float m_MantleMaxAlignmentAngle = 55;

	TWeakObjectPtr<APlayerCharacter> m_PlayerCharacter = nullptr;

	EMovementMode m_LastMode = EMovementMode::MOVE_Walking;

	bool m_IsSprinting = false;
	bool m_IsCrouching = false;
};
