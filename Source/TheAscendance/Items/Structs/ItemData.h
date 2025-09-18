// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheAscendance/Items/Enums/ItemType.h"
#include "TheAscendance/Core/CoreMacros.h"
#include "TheAscendance/Items/Structs/WeaponData.h"
#include "ItemData.generated.h"

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int ItemID = 0;
	UPROPERTY(EditDefaultsOnly)
	FName ItemName = "";
	UPROPERTY(EditDefaultsOnly)
	EItemType ItemType = EItemType::DEFAULT;
	UPROPERTY(EditDefaultsOnly)
	FString ItemDescription = "";
	UPROPERTY(EditDefaultsOnly)
	bool IsStackable = true;
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UStaticMesh> ItemMesh = nullptr;

	FItemData() {}

	FItemData(FItemData& itemData) = default;
};

