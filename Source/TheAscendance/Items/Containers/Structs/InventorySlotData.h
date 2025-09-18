// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventorySlotData.generated.h"

USTRUCT()
struct FInventorySlotData
{
	GENERATED_BODY()

	int InventoryIndex = -1;
	int ItemID = 0;
	int ItemAmount = 0;
};
