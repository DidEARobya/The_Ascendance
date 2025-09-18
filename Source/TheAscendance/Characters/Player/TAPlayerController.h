// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TAPlayerController.generated.h"

class UInputMappingContext;
class UEnhancedInputComponent;
class UInputAction;
class UCharacterMovementComponent;
class APlayerCharacter;

UCLASS()
class THEASCENDANCE_API ATAPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void DisplayHUD();

protected:
	//---- INPUT HANDLERS ----
	void HandleLook(const struct FInputActionValue& value);
	void HandleMove(const struct FInputActionValue& value);
	void HandleJump();
	void HandleStartSprint();
	void HandleEndSprint();
	void HandleStartCrouch();
	void HandleEndCrouch();

	void HandleMainHandPrimaryAttack();
	void HandleMainHandSecondaryAttack();

	void HandleOffhandPrimaryAttack();
	void HandleOffhandSecondaryAttack();

	void HandleToggleInventory();
	void HandleToggleQuestMenu();
	void HandleTogglePauseMenu();
	void HandleInteract();

	void HandleTestFunction1();
	void HandleTestFunction2();
	void HandleTestFunction3();

	virtual void OnPossess(APawn* pawn) override;
	virtual void OnUnPossess() override;
private:
	void BindActions(UEnhancedInputComponent* enhancedInputComponent);

public:
	UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0.01", ClampMax = "1.0"))
	float HorizontalSensitivity;
	UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0.01", ClampMax = "1.0"))
	float VerticalSensitivity;

	//---- INPUTS ----
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Mapping Context")
	TObjectPtr<UInputMappingContext> InputMappingContext = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Character Movement")
	TObjectPtr<UInputAction> ActionLook = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Character Movement")
	TObjectPtr<UInputAction> ActionMove = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Character Movement")
	TObjectPtr<UInputAction> ActionJump = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Character Movement")
	TObjectPtr<UInputAction> ActionSprint = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Character Movement")
	TObjectPtr<UInputAction> ActionCrouch = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Character Actions")
	TObjectPtr<UInputAction> ActionToggleInventory = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Character Actions")
	TObjectPtr<UInputAction> ActionToggleQuestMenu = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Character Actions")
	TObjectPtr<UInputAction> ActionMainHandPrimaryAttack = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Character Actions")
	TObjectPtr<UInputAction> ActionMainHandSecondaryAttack = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Character Actions")
	TObjectPtr<UInputAction> ActionOffHandPrimaryAttack = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Character Actions")
	TObjectPtr<UInputAction> ActionOffHandSecondaryAttack = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Character Actions")
	TObjectPtr<UInputAction> ActionTogglePauseMenu = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Character Actions")
	TObjectPtr<UInputAction> ActionInteract = nullptr;

	//Test
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Test Actions")
	TObjectPtr<UInputAction> ActionTestFunction1 = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Test Actions")
	TObjectPtr<UInputAction> ActionTestFunction2 = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Global | Test Actions")
	TObjectPtr<UInputAction> ActionTestFunction3 = nullptr;

private:
	UPROPERTY()
	TObjectPtr<UEnhancedInputComponent> m_EnhancedInputComponent = nullptr;
	TWeakObjectPtr<APlayerCharacter> m_PlayerCharacter = nullptr;
};
