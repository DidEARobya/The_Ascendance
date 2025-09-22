// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TheAscendance/Spells/Interfaces/Spell.h"
#include "SpellBase.generated.h"

class ISpellCaster;
class USpellData;

UCLASS(Abstract)
class THEASCENDANCE_API USpellBase : public UObject, public ISpell
{
	GENERATED_BODY()
	
public:
	virtual void Init(USpellData* spellData, ISpellCaster* spellOwner) override;

	virtual bool CanCast() override;
	virtual bool CastSpell() override;

	virtual void Update(float deltaTime) override;

	virtual void OnHit(AActor* hitActor, FVector spellHitLocation) override;
	virtual void ProcessHit(FVector spellHitLocation) override;
	virtual TArray<TObjectPtr<AActor>> GetHitActors() override;

	virtual void Fire(FVector direction) override;

	virtual ISpellCaster* GetSpellOwner() override;


protected:
	UPROPERTY()
	TScriptInterface<ISpellCaster> m_SpellOwner = nullptr;

	UPROPERTY()
	TArray<TObjectPtr<AActor>> m_HitActors;

private:
	float m_Cooldown = 0.0f;
	float m_CooldownTimer = 0.0f;
};
