// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TheAscendance/Items/Containers/Structs/InventorySlotData.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEASCENDANCE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	void SetInventory(const TArray<FInventorySlotData>& inventory);
	void AddItem(int id, int amount);

	void RemoveItem(int id, int amount);
	void RemoveItemAtIndex(int index, int amount);

	int GetItemCount(int id);
	const TArray<TSharedRef<FInventorySlotData>>& GetInventory();

	TSharedPtr<FInventorySlotData> GetInventorySlotDataAtIndex(int index);

	bool Contains(int id);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	TSharedPtr<FInventorySlotData> GetInventorySlotData(int id);
	void RemoveItemFromArray(int index);

private:
	TArray<TSharedRef<FInventorySlotData>> m_Inventory;
};
