// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TheAscendance/Spells/Interfaces/Spell.h"
#include "SpellBase.generated.h"

class ISpellCaster;

UCLASS(Abstract)
class THEASCENDANCE_API USpellBase : public UObject, public ISpell
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	virtual bool CastSpell() override;

	virtual void Update(float deltaTime) override;
	virtual void ProcessHit(AActor* target, FVector location) override;

	virtual void Fire(FVector direction) override;

protected:
	UPROPERTY()
	TScriptInterface<ISpellCaster> m_SpellOwner;

private:
	float m_Cooldown;
	float m_CooldownTimer;
};
