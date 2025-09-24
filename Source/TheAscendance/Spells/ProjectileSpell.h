// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSpell.h"
#include "ProjectileSpell.generated.h"

class UProjectileSpellData;

UCLASS()
class THEASCENDANCE_API UProjectileSpell : public UBaseSpell
{
	GENERATED_BODY()
	
public:
	virtual void Init(USpellData* spellData, ISpellCaster* spellOwner) final;

	virtual bool CastSpell() override;
	virtual void Fire(FVector direction) override;

	virtual void ProcessOverlapDamage(int& damage) override;
	virtual void ProcessHitDamage(int& damage, FVector targetLocation, FVector hitLocation) override;

	virtual void DealDamage(AActor* hitActor, int damage) override;

private:
	TWeakObjectPtr<UProjectileSpellData> m_SpellData = nullptr;
};
