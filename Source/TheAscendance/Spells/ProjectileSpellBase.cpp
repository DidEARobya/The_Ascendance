// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileSpellBase.h"
#include "TheAscendance/Core/CoreMacros.h"
#include "Interfaces/SpellCaster.h"
#include "Structs/SpellData.h"

void UProjectileSpellBase::Init(USpellData* spellData, ISpellCaster* spellOwner)
{
	USpellBase::Init(spellData, spellOwner);

	if (spellData == nullptr || spellOwner == nullptr)
	{
		return;
	}

	if (UProjectileSpellData* data = Cast<UProjectileSpellData>(spellData))
	{
		m_SpellData = data;
	}
	else
	{
		LOG_ERROR("Tried to Init ProjectileSpellBase with invalid SpellData");
	}
}

bool UProjectileSpellBase::CastSpell()
{
	if (USpellBase::CastSpell() == false)
	{
		return false;
	}

	FVector unitDirection = GetSpellOwner()->GetCastStartForward();
	unitDirection.Normalize();

	Fire(unitDirection);

	return true;
}

void UProjectileSpellBase::Fire(FVector direction)
{
	USpellBase::Fire(direction);

	LOG_ONSCREEN(-1, 1.0f, FColor::Cyan, "Projectile: Fire");
}
