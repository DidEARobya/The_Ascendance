// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheAscendance/Characters/Enums/EquippablePart.h"
#include "LoadoutSlotData.generated.h"

USTRUCT()
struct FLoadoutSlotData
{
	GENERATED_BODY()

	int ItemID = 0;
	EEquippablePart EquippedPart = EEquippablePart::NONE;
};
