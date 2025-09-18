// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableGameMode.h"
#include "TheAscendance/Game/DataLoaders/ItemLoader.h"
#include "TheAscendance/Core/CoreMacros.h"

FItemData* APlayableGameMode::GetItemData(int id)
{
	if (m_ItemLoader == nullptr)
	{
		return nullptr;
	}

	return m_ItemLoader->GetItemData(id);
}

FWeaponData* APlayableGameMode::GetWeaponData(int id)
{
	if (m_ItemLoader == nullptr)
	{
		return nullptr;
	}

	return m_ItemLoader->GetWeaponData(id);
}

const FWeaponTypeData* APlayableGameMode::GetWeaponTypeData(EWeaponType type)
{
	if (m_ItemLoader == nullptr)
	{
		return nullptr;
	}

	return m_ItemLoader->GetWeaponTypeData(type);
}

void APlayableGameMode::InitGameState()
{
	Super::InitGameState();

#if WITH_EDITOR
	if (GIsEditor && !GetWorld()->IsGameWorld())
	{
		LOG_INFO("Opened PlayableGameMode BP in Editor");
		return;
	}
#endif

	if (m_ItemLoader = NewObject<UItemLoader>())
	{
		m_ItemLoader->Init();
	}
	else
	{
		LOG_ERROR("PlayableGameMode failed to create ItemLoader");
	}

}

void APlayableGameMode::StartPlay()
{
	Super::StartPlay();
}

void APlayableGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void APlayableGameMode::StartToLeaveMap()
{
	// Save Logic
	Super::StartToLeaveMap();
}


