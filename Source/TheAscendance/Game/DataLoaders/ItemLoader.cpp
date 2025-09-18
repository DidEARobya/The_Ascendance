// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemLoader.h"
#include "TheAscendance/Core/CoreFunctionLibrary.h"
#include "TheAscendance/Core/CoreMacros.h"
#include "TheAscendance/Game/Subsystems/DataHandlerSubsystem.h"
#include "TheAscendance/Items/Structs/ItemData.h"
#include "TheAscendance/Items/Structs/WeaponData.h"

void UItemLoader::Init()
{
	if (UDataHandlerSubsystem* dataHandler = UCoreFunctionLibrary::GetDataHandlerSubsystem())
	{
		 m_ItemTable = dataHandler->LoadData(EDataGroup::ITEMS);

		if (m_ItemTable == nullptr)
		{
			LOG_ERROR("ItemLoader failed to load Item DataTable");
		}
		else
		{
			LOG_INFO("ItemLoader succeeded to load Item DataTable");
		}

		m_WeaponTable = dataHandler->LoadData(EDataGroup::WEAPONS);

		if (m_WeaponTable == nullptr)
		{
			LOG_ERROR("ItemLoader failed to load Weapon DataTable");
		}
		else
		{
			LOG_INFO("ItemLoader succeeded to load Weapon DataTable");
		}

		m_WeaponTypeData = &dataHandler->GetWeaponTypeMap();
	}
}

FItemData* UItemLoader::GetItemData(int itemID)
{
	if (m_ItemTable == nullptr)
	{
		LOG_ERROR("ItemLoader tried to load ItemData without a valid ItemTable");
		return nullptr;
	}

	static const FString contextString(TEXT("Item Context String"));

	TArray<FItemData*> itemStructs;
	m_ItemTable->GetAllRows(contextString, itemStructs);

	for (const auto data : itemStructs)
	{
		if (data->ItemID == itemID)
		{
			return data;
		}
	}

	LOG_ERROR("ItemLoader could not load ItemData for Item ID: %i", itemID);
	return nullptr;
}

FWeaponData* UItemLoader::GetWeaponData(int itemID)
{
	if (m_WeaponTable == nullptr)
	{
		LOG_ERROR("ItemLoader tried to load Equippable without a valid WeaponTable");
		return nullptr;
	}

	static const FString contextString(TEXT("Weapon Context String"));

	TArray<FWeaponData*> weaponStructs;
	m_WeaponTable->GetAllRows(contextString, weaponStructs);

	for (const auto weaponData : weaponStructs)
	{
		if (weaponData->ItemID == itemID)
		{
			return weaponData;
		}
	}

	LOG_ERROR("ItemLoader could not load WeaponData for Item ID: %i", itemID);
	return nullptr;
}

const FWeaponTypeData* UItemLoader::GetWeaponTypeData(EWeaponType type)
{
	if (m_WeaponTypeData == nullptr || m_WeaponTypeData->Contains(type) == false)
	{
		LOG_ERROR("WeaponTypeData doesn't contain data for Weapon Type: %s", *UEnum::GetValueAsString(type));
		return nullptr;
	}

	return &(*m_WeaponTypeData)[type];
}
