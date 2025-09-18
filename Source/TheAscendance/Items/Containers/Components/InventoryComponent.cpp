// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "TheAscendance/Core/CoreMacros.h"
#include "TheAscendance/Core/CoreFunctionLibrary.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::SetInventory(const TArray<FInventorySlotData>& inventory)
{
	for (const auto data : inventory)
	{
		m_Inventory.Add(MakeShared<FInventorySlotData>(data));
	}
}

void UInventoryComponent::AddItem(int id, int amount)
{
	if (APlayableGameMode* gameMode = UCoreFunctionLibrary::GetPlayableGameMode())
	{
		//FItemData* itemData = gameMode->GetItemData(id);

		//if (itemData == nullptr)
		//{
		//	return;
		//}

		if (/*itemData->isStackable == true && */Contains(id) == true)
		{
			GetInventorySlotData(id)->ItemAmount += amount;
		}
		else
		{
			int index = m_Inventory.Num();
			m_Inventory.Add(MakeShared<FInventorySlotData>(index, id, amount));
		}
	}
}

void UInventoryComponent::RemoveItem(int id, int amount)
{
	TSharedPtr<FInventorySlotData> data = GetInventorySlotData(id);

	if (data == nullptr)
	{
		LOG_WARNING("InventorySlotData doesn't exist with item ID: %i", id);
		return;
	}

	data->ItemAmount -= amount;

	if (data->ItemAmount <= 0)
	{
		RemoveItemFromArray(data->InventoryIndex);
	}
}

void UInventoryComponent::RemoveItemAtIndex(int index, int amount)
{
	if (index < 0 || index >= m_Inventory.Num())
	{
		return;
	}

	TSharedPtr<FInventorySlotData> data = GetInventorySlotDataAtIndex(index);

	if (data == nullptr)
	{
		LOG_ERROR("InventorySlotData doesn't exist at index: %i", index);
		return;
	}

	data->ItemAmount -= amount;

	if (data->ItemAmount <= 0)
	{
		RemoveItemFromArray(data->InventoryIndex);
	}
}

int UInventoryComponent::GetItemCount(int id)
{
	TSharedPtr<FInventorySlotData> data = GetInventorySlotData(id);

	if (data == nullptr)
	{
		LOG_WARNING("InventorySlotData doesn't exist with item ID: %i", id);
		return 0;
	}

	return data->ItemAmount;
}

const TArray<TSharedRef<FInventorySlotData>>& UInventoryComponent::GetInventory()
{
	return m_Inventory;
}

TSharedPtr<FInventorySlotData> UInventoryComponent::GetInventorySlotDataAtIndex(int index)
{
	if (index < 0 || index >= m_Inventory.Num())
	{
		return nullptr;
	}

	return m_Inventory[index];
}

bool UInventoryComponent::Contains(int id)
{
	for (const auto data : m_Inventory)
	{
		if (data->ItemID == id)
		{
			return true;
		}
	}

	return false;
}

TSharedPtr<FInventorySlotData> UInventoryComponent::GetInventorySlotData(int id)
{
	for (const auto data : m_Inventory)
	{
		if (data->ItemID == id)
		{
			return data;
		}
	}

	return nullptr;
}

void UInventoryComponent::RemoveItemFromArray(int index)
{
	m_Inventory.RemoveAt(index);

	for (const auto data : m_Inventory)
	{
		if (data->InventoryIndex > index)
		{
			data->InventoryIndex -= 1;
		}
	}
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

