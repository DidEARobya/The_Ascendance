// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadoutComponent.h"

// Sets default values for this component's properties
ULoadoutComponent::ULoadoutComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void ULoadoutComponent::EquipItem(EEquippablePart part, int itemID)
{
	UnEquipItem(part);

	m_Loadout.Add(MakeShared<FLoadoutSlotData>(itemID, part));
}

void ULoadoutComponent::UnEquipItem(EEquippablePart part)
{
	for (const auto data : m_Loadout)
	{
		if (data->EquippedPart == part)
		{
			//Unequip Logic
			return;
		}
	}
}

void ULoadoutComponent::SetSpells(const TArray<int>& spells)
{
	m_Spells = spells;
}

// Called when the game starts
void ULoadoutComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool ULoadoutComponent::Contains(EEquippablePart part)
{
	for (const auto data : m_Loadout)
	{
		if (data->EquippedPart == part)
		{
			return true;
		}
	}

	return false;
}

