// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellDecorator.h"

void USpellDecorator::Decorate(ISpell* decorator)
{
	if (decorator == nullptr)
	{
		LOG_ERROR("Tried to decorate with invalid decorator");
		return;
	}

	m_DecoratedSpell = decorator->_getUObject();
}

bool USpellDecorator::CanCast()
{
	if (m_DecoratedSpell == nullptr)
	{
		LOG_ERROR("Spell decorater has invalid DecoratedSpell pointer");
		return false;
	}

	return m_DecoratedSpell->CanCast();
}

bool USpellDecorator::CastSpell()
{
	if (m_DecoratedSpell == nullptr)
	{
		LOG_ERROR("Spell decorater has invalid DecoratedSpell pointer");
		return false;
	}

	return m_DecoratedSpell->CastSpell();
}

void USpellDecorator::Update(float deltaTime)
{
	if (m_DecoratedSpell == nullptr)
	{
		LOG_ERROR("Spell decorater has invalid DecoratedSpell pointer");
		return;
	}

	m_DecoratedSpell->Update(deltaTime);
}

void USpellDecorator::ProcessHit(AActor* target, FVector location)
{
	if (m_DecoratedSpell == nullptr)
	{
		LOG_ERROR("Spell decorater has invalid DecoratedSpell pointer");
		return;
	}

	m_DecoratedSpell->ProcessHit(target, location);
}

void USpellDecorator::Fire(FVector direction)
{
	if (m_DecoratedSpell == nullptr)
	{
		LOG_ERROR("Spell decorater has invalid DecoratedSpell pointer");
		return;
	}

	m_DecoratedSpell->Fire(direction);
}

ISpellCaster* USpellDecorator::GetSpellOwner()
{
	if (m_DecoratedSpell == nullptr)
	{
		LOG_ERROR("Spell decorater has invalid DecoratedSpell pointer");
		return nullptr;
	}

	return m_DecoratedSpell->GetSpellOwner();
}