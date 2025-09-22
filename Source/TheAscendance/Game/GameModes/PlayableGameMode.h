// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TheAscendance/Items/Enums/WeaponType.h"
#include "PlayableGameMode.generated.h"

class USpellLoader;
class ISpell;
class ISpellCaster;
class UItemLoader;
struct FItemData;
struct FWeaponData;
struct FWeaponTypeData;

UCLASS(Blueprintable)
class THEASCENDANCE_API APlayableGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	FItemData* GetItemData(int id);
	FWeaponData* GetWeaponData(int itemID);
	const FWeaponTypeData* GetWeaponTypeData(EWeaponType type);

	ISpell* CreateSpellFromID(int spellID, ISpellCaster* spellOwner);

	virtual void InitGameState() override;

	virtual void StartPlay() override;
	virtual void StartToLeaveMap() override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UItemLoader> m_ItemLoader = nullptr;
	UPROPERTY()
	TObjectPtr<USpellLoader> m_SpellLoader = nullptr;
};
