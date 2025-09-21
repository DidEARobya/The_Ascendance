// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellBase.h"

void USpellBase::Init()
{
}

bool USpellBase::CastSpell()
{
	if (m_CooldownTimer > 0.0f)
	{
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

void USpellBase::ProcessHit(AActor* target, FVector location)
{
}

void USpellBase::Fire(FVector direction)
{
}
