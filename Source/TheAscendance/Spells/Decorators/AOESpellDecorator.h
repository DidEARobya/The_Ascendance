// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellDecorator.h"
#include "AOESpellDecorator.generated.h"

UCLASS()
class THEASCENDANCE_API UAOESpellDecorator : public USpellDecorator
{
	GENERATED_BODY()
	
public:
	class THEASCENDANCE_API Builder
	{
		TWeakObjectPtr<UAOESpellDecorator> m_Decorator = nullptr;

	public:
		Builder(ISpell* decorator)
		{
			m_Decorator = NewObject<UAOESpellDecorator>();
			m_Decorator->Decorate(decorator);
		}
		ISpell* Build()
		{
			if (m_Decorator.IsValid() == false)
			{
				LOG_ERROR("Tried to build AOESpellDecorator without initialising it.")
				return nullptr;
			}

			return m_Decorator.Get();
		}
	};

	virtual bool CastSpell() override;

	//Test
	virtual void Fire(FVector direction) override;
};
