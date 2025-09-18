// Fill out your copyright notice in the Description page of Project Settings.
#include "TAPlayerController.h"
#include "TheAscendance/Core/CoreMacros.h"
#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void ATAPlayerController::DisplayHUD()
{
}

void ATAPlayerController::HandleLook(const FInputActionValue& value)
{
	const FVector rotationVector = value.Get<FVector>();

	AddYawInput(rotationVector.X * HorizontalSensitivity);
	AddPitchInput(rotationVector.Y * VerticalSensitivity);
}

void ATAPlayerController::HandleMove(const FInputActionValue& value)
{
	if (m_PlayerCharacter.IsValid() == false)
	{
		LOG_ERROR("PlayerController has lost it's reference to the PlayerCharacter");
		return;
	}

	const FVector movementVector = value.Get<FVector>();

	m_PlayerCharacter->AddMovementInput(m_PlayerCharacter->GetActorForwardVector(), movementVector.Y);
	m_PlayerCharacter->AddMovementInput(m_PlayerCharacter->GetCamera()->GetRightVector(), movementVector.X);
}

void ATAPlayerController::HandleJump()
{
	if (m_PlayerCharacter.IsValid() == false)
	{
		LOG_ERROR("PlayerController has lost it's reference to the PlayerCharacter");
		return;
	}

	m_PlayerCharacter->SetIsJumping();
	m_PlayerCharacter->Jump();
}

void ATAPlayerController::HandleStartSprint()
{
	if (m_PlayerCharacter.IsValid() == false)
	{
		LOG_ERROR("PlayerController has lost it's reference to the PlayerCharacter");
		return;
	}

	m_PlayerCharacter->SetIsSprinting(true);
}

void ATAPlayerController::HandleEndSprint()
{
	if (m_PlayerCharacter.IsValid() == false)
	{
		LOG_ERROR("PlayerController has lost it's reference to the PlayerCharacter");
		return;
	}

	m_PlayerCharacter->SetIsSprinting(false);
}

void ATAPlayerController::HandleStartCrouch()
{
	if (m_PlayerCharacter.IsValid() == false)
	{
		LOG_ERROR("PlayerController has lost it's reference to the PlayerCharacter");
		return;
	}

	m_PlayerCharacter->SetIsCrouching(true);
}

void ATAPlayerController::HandleEndCrouch()
{
	if (m_PlayerCharacter.IsValid() == false)
	{
		LOG_ERROR("PlayerController has lost it's reference to the PlayerCharacter");
		return;
	}

	m_PlayerCharacter->SetIsCrouching(false);
}

void ATAPlayerController::HandleMainHandPrimaryAttack()
{
	if (m_PlayerCharacter.IsValid() == false)
	{
		LOG_ERROR("PlayerController has lost it's reference to the PlayerCharacter");
		return;
	}

	m_PlayerCharacter->MainHandPrimaryAttack();
}

void ATAPlayerController::HandleMainHandSecondaryAttack()
{
	if (m_PlayerCharacter.IsValid() == false)
	{
		LOG_ERROR("PlayerController has lost it's reference to the PlayerCharacter");
		return;
	}

	m_PlayerCharacter->MainHandSecondaryAttack();
}

void ATAPlayerController::HandleOffhandPrimaryAttack()
{
	if (m_PlayerCharacter.IsValid() == false)
	{
		LOG_ERROR("PlayerController has lost it's reference to the PlayerCharacter");
		return;
	}

	m_PlayerCharacter->OffHandPrimaryAttack();
}

void ATAPlayerController::HandleOffhandSecondaryAttack()
{
	if (m_PlayerCharacter.IsValid() == false)
	{
		LOG_ERROR("PlayerController has lost it's reference to the PlayerCharacter");
		return;
	}

	m_PlayerCharacter->OffHandSecondaryAttack();
}

void ATAPlayerController::HandleToggleInventory()
{
}

void ATAPlayerController::HandleToggleQuestMenu()
{
}

void ATAPlayerController::HandleTogglePauseMenu()
{
}

void ATAPlayerController::HandleInteract()
{
}

void ATAPlayerController::HandleTestFunction1()
{
	if (m_PlayerCharacter.IsValid() == false)
	{
		LOG_ERROR("PlayerController has lost it's reference to the PlayerCharacter");
		return;
	}

	m_PlayerCharacter->TestFunction1();
}

void ATAPlayerController::HandleTestFunction2()
{
	if (m_PlayerCharacter.IsValid() == false)
	{
		LOG_ERROR("PlayerController has lost it's reference to the PlayerCharacter");
		return;
	}

	m_PlayerCharacter->TestFunction2();
}

void ATAPlayerController::HandleTestFunction3()
{
	if (m_PlayerCharacter.IsValid() == false)
	{
		LOG_ERROR("PlayerController has lost it's reference to the PlayerCharacter");
		return;
	}

	m_PlayerCharacter->TestFunction3();
}

void ATAPlayerController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);

	//if (TObjectPtr<UUIManagerSubsystem> uiManager = GetGameInstance()->GetSubsystem<UUIManagerSubsystem>())
	//{
	//	_uiManager = uiManager;
	//	_uiManager->CreateWidgets(this);
	//}

	m_PlayerCharacter = Cast<APlayerCharacter>(pawn);

	if (m_PlayerCharacter.IsValid() == false)
	{
		LOG_ERROR("PlayerController failed to store reference to PlayerCharacter");
		return;
	}

	m_PlayerCharacter->SetPlayerController(this);

	m_EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(m_EnhancedInputComponent, TEXT("ENHANCED_INPUT_COMPONENT is an invalid value"));

	UEnhancedInputLocalPlayerSubsystem* inputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(inputSubsystem, TEXT("INPUT_SUBSYSTEM is an invalid value"));

	checkf(InputMappingContext, TEXT("INPUT_MAPPING_CONTEXT is an invalid value"));
	inputSubsystem->ClearAllMappings();
	inputSubsystem->AddMappingContext(InputMappingContext, 0);

	BindActions(m_EnhancedInputComponent);
}

void ATAPlayerController::OnUnPossess()
{
	if (m_EnhancedInputComponent != nullptr)
	{
		m_EnhancedInputComponent->ClearActionBindings();
	}

	Super::OnUnPossess();
}

void ATAPlayerController::BindActions(UEnhancedInputComponent* enhancedInputComponent)
{
	checkf(ActionLook, TEXT("Missing 'Look' Action"));
	enhancedInputComponent->BindAction(ActionLook, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleLook);

	checkf(ActionMove, TEXT("Missing 'Move' Action"));
	enhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleMove);

	checkf(ActionJump, TEXT("Missing 'Jump' Action"));
	enhancedInputComponent->BindAction(ActionJump, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleJump);

	checkf(ActionSprint, TEXT("Missing 'Sprint' Action"));
	enhancedInputComponent->BindAction(ActionSprint, ETriggerEvent::Started, this, &ATAPlayerController::HandleStartSprint);
	enhancedInputComponent->BindAction(ActionSprint, ETriggerEvent::Completed, this, &ATAPlayerController::HandleEndSprint);

	checkf(ActionSprint, TEXT("Missing 'Crouch' Action"));
	enhancedInputComponent->BindAction(ActionCrouch, ETriggerEvent::Started, this, &ATAPlayerController::HandleStartCrouch);
	enhancedInputComponent->BindAction(ActionCrouch, ETriggerEvent::Completed, this, &ATAPlayerController::HandleEndCrouch);

	checkf(ActionToggleInventory, TEXT("Missing 'Toggle Inventory' Action"));
	enhancedInputComponent->BindAction(ActionToggleInventory, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleToggleInventory);

	checkf(ActionToggleQuestMenu, TEXT("Missing 'Toggle Quest Menu' Action"));
	enhancedInputComponent->BindAction(ActionToggleQuestMenu, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleToggleQuestMenu);

	checkf(ActionMainHandPrimaryAttack, TEXT("Missing 'Main Hand Primary Attack' Action"));
	enhancedInputComponent->BindAction(ActionMainHandPrimaryAttack, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleMainHandPrimaryAttack);
	checkf(ActionMainHandSecondaryAttack, TEXT("Missing 'Main Hand Alt Attack' Action"));
	enhancedInputComponent->BindAction(ActionMainHandSecondaryAttack, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleMainHandSecondaryAttack);

	checkf(ActionOffHandPrimaryAttack, TEXT("Missing 'Offhand Primary Attack' Action"));
	enhancedInputComponent->BindAction(ActionOffHandPrimaryAttack, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleOffhandPrimaryAttack);
	checkf(ActionOffHandSecondaryAttack, TEXT("Missing 'Offhand Alt Attack' Action"));
	enhancedInputComponent->BindAction(ActionOffHandSecondaryAttack, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleOffhandSecondaryAttack);

	checkf(ActionTogglePauseMenu, TEXT("Missing 'TogglePauseMenu' Action"));
	enhancedInputComponent->BindAction(ActionTogglePauseMenu, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleTogglePauseMenu);

	checkf(ActionInteract, TEXT("Missing 'Interact' Action"));
	enhancedInputComponent->BindAction(ActionInteract, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleInteract);

	checkf(ActionTestFunction1, TEXT("Missing 'TestFunction1' Action"));
	enhancedInputComponent->BindAction(ActionTestFunction1, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleTestFunction1);

	checkf(ActionTestFunction2, TEXT("Missing 'TestFunction2' Action"));
	enhancedInputComponent->BindAction(ActionTestFunction2, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleTestFunction2);

	checkf(ActionTestFunction3, TEXT("Missing 'TestFunction3' Action"));
	enhancedInputComponent->BindAction(ActionTestFunction3, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleTestFunction3);
}
