// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellBase.h"
#include "TheAscendance/Core/CoreMacros.h"
#include "Interfaces/SpellCaster.h"

void USpellBase::Init(USpellData* spellData, ISpellCaster* spellOwner)
{
	if (spellData == nullptr || spellOwner == nullptr)
	{
		LOG_ERROR("Tried to Init spell with invalid SpellData or SpellOwner");
		return;
	}

	m_SpellOwner = spellOwner->_getUObject();
}

bool USpellBase::CanCast()
{
	if (m_CooldownTimer > 0.0f)
	{
		return false;
	}

	return true;
}

bool USpellBase::CastSpell()
{
	if (m_CooldownTimer > 0.0f)
	{
		LOG_WARNING("Check CanCast before calling CastSpell");
		LOG_ONSCREEN(-1, 5.0f, FColor::Yellow, "Check CanCast before calling CastSpell");
		return false;
	}

	m_CooldownTimer = m_Cooldown;
	return true;
}

void USpellBase::Update(float deltaTime)
{
	if (m_Cooldown < 0)
	{
		return;
	}

	m_CooldownTimer -= deltaTime;
}

void USpellBase::OnOverlap(AActor* overlapActor, FVector spellOverlapLocation)
{		
	//Deal Damage

	//Check if Dead

	//Handle Effects
}

void USpellBase::OnHit(AActor* hitActor, FVector spellHitLocation)
{
	if (hitActor != nullptr && m_HitActors.Contains(hitActor) == false)
	{
		m_HitActors.Add(hitActor);
	}

	ProcessHit(spellHitLocation);
}

void USpellBase::ProcessHit(FVector spellHitLocation)
{
	for (auto actor : m_HitActors)
	{
		//Deal Damage

		//Check if Dead

		//Handle Effects
	}

	m_HitActors.Empty();
}

void USpellBase::Fire(FVector direction)
{
	LOG_ONSCREEN(-1, 1.0f, FColor::Cyan, "Base: Fire");
}

ISpellCaster* USpellBase::GetSpellOwner()
{
	if (m_SpellOwner == nullptr)
	{
		LOG_ERROR("Spell has invalid SpellOwner");
		return nullptr;
	}

	return m_SpellOwner.GetInterface();
}

TArray<TObjectPtr<AActor>> USpellBase::GetHitActors()
{
	return m_HitActors;
}
