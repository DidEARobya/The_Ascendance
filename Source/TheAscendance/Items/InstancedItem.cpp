// Fill out your copyright notice in the Description page of Project Settings.


#include "InstancedItem.h"
#include "TheAscendance/Core/CoreFunctionLibrary.h"
#include "TheAscendance/Core/CoreMacros.h"
#include "TheAscendance/Game/GameModes/PlayableGameMode.h"

// Called when the game starts or when spawned
void AInstancedItem::BeginPlay()
{
	Super::BeginPlay();
	
	if (m_InstanceID == 0)
	{
		LOG_ERROR("Tried to create InstancedItem with ID of 0");
		return;
	}

	if (APlayableGameMode* gameMode = UCoreFunctionLibrary::GetPlayableGameMode())
	{
		Init(gameMode->GetItemData(m_InstanceID));
	}
	else
	{
		LOG_ERROR("Tried to create InstancedItem in world without PlayableGameMode");
	}
}


