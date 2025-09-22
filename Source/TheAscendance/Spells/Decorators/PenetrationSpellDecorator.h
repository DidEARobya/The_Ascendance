// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellDecorator.h"
#include "PenetrationSpellDecorator.generated.h"

/**
 * 
 */
UCLASS()
class THEASCENDANCE_API UPenetrationSpellDecorator : public USpellDecorator
{
	GENERATED_BODY()

public:
	class THEASCENDANCE_API Builder
	{
		TWeakObjectPtr<UPenetrationSpellDecorator> m_Decorator = nullptr;

	public:
		Builder(ISpell* decorator)
		{
			m_Decorator = NewObject<UPenetrationSpellDecorator>();
			m_Decorator->Decorate(decorator);
		}
		ISpell* Build()
		{
			if (m_Decorator.IsValid() == false)
			{
				LOG_ERROR("Tried to build PenetrationSpellDecorator without initialising it.")
				return nullptr;
			}

			return m_Decorator.Get();
		}
	};

	virtual bool CastSpell() override;

	//Test
	virtual void Fire(FVector direction) override;
};
