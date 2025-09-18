// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheAscendance/Items/Structs/WeaponData.h"
#include "TheAscendance/Items/Enums/WeaponType.h"
#include "ItemLoader.generated.h"

struct FItemData;
struct FWeaponData;

UCLASS()
class THEASCENDANCE_API UItemLoader : public UObject
{
	GENERATED_BODY()

public:
	void Init();

	FItemData* GetItemData(int itemID);
	FWeaponData* GetWeaponData(int itemID);
	const FWeaponTypeData* GetWeaponTypeData(EWeaponType type);

private:
	UPROPERTY()
	TObjectPtr<UDataTable> m_ItemTable = nullptr;

	UPROPERTY()
	TObjectPtr<UDataTable> m_WeaponTable = nullptr;

	const TMap<EWeaponType, FWeaponTypeData>* m_WeaponTypeData;
};
