// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreFunctionLibrary.h"
#include "TheAscendance/Characters/Player/PlayerCharacter.h"
#include "TheAscendance/Characters/Player/TAPlayerController.h"
#include "TheAscendance/Game/GameModes/PlayableGameMode.h"
#include "TheAscendance/Game/Subsystems/DataHandlerSubsystem.h"
#include "TheAscendance/Core/CoreMacros.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"

UWorld* UCoreFunctionLibrary::GetGameWorld()
{
	if (UGameViewportClient* viewport = GEngine->GameViewport)
	{
		return viewport->GetWorld();
	}

	LOG_ERROR("GameViewport was invalid");
	return nullptr;
}

APlayableGameMode* UCoreFunctionLibrary::GetPlayableGameMode()
{
	if (UWorld* world = GetGameWorld())
	{
		return world->GetAuthGameMode<APlayableGameMode>();
	}

	LOG_ERROR("GameWorld was invalid");
	return nullptr;
}

APlayerCharacter* UCoreFunctionLibrary::GetPlayerCharacter()
{
	if (APlayerCharacter* player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetGameWorld(), 0)))
	{
		return player;
	}

	LOG_ERROR("PlayerCharacter was invalid");
	return nullptr;
}

ATAPlayerController* UCoreFunctionLibrary::GetPlayerController()
{
	if (ATAPlayerController* controller = Cast<ATAPlayerController>(UGameplayStatics::GetPlayerController(GetGameWorld(), 0)))
	{
		return controller;
	}

	LOG_ERROR("PlayerController was invalid");
	return nullptr;
}

void UCoreFunctionLibrary::LogInfo(FString string)
{
	LOG_INFO("%s", *string);
}

void UCoreFunctionLibrary::LogWarning(FString string)
{
	LOG_WARNING("%s", *string);
}

void UCoreFunctionLibrary::LogError(FString string)
{
	LOG_ERROR("%s", *string);
}

UDataHandlerSubsystem* UCoreFunctionLibrary::GetDataHandlerSubsystem()
{
	if (UWorld* world = GetGameWorld())
	{
		return world->GetGameInstance()->GetSubsystem<UDataHandlerSubsystem>();
	}

	LOG_ERROR("GameWorld was invalid");
	return nullptr;
}

void UCoreFunctionLibrary::RequestAsyncLoad(const FSoftObjectPath& targetToStream, TFunction<void()> delegate)
{
	LOG_INFO("Requesting ASync Load for: %s", *targetToStream.ToString());

	if (delegate == nullptr)
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(targetToStream);
		return;
	}

	UAssetManager::GetStreamableManager().RequestAsyncLoad(targetToStream, FStreamableDelegate::CreateLambda(delegate));
}
