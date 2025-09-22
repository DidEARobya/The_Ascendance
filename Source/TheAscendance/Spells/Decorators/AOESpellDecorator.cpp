// Fill out your copyright notice in the Description page of Project Settings.


#include "AOESpellDecorator.h"
#include "TheAscendance/Spells/Interfaces/SpellCaster.h"

bool UAOESpellDecorator::CastSpell()
{
	if (m_DecoratedSpell == nullptr)
	{
		LOG_ERROR("AOESpellDecorator has no decorated spell");
		return false;
	}

	FVector unitDirection = m_DecoratedSpell->GetSpellOwner()->GetCastStartForward();
	unitDirection.Normalize();

	Fire(unitDirection);

	return true;
}

void UAOESpellDecorator::Fire(FVector direction)
{
	m_DecoratedSpell->Fire(direction);

	LOG_ONSCREEN(-1, 1.0f, FColor::Cyan, "AOE Decorator: Fire");
}
