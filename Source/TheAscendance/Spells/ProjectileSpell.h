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

	//virtual void Update(float deltaTime) override;
	//virtual void ProcessHit(AActor* target, FVector location) override;

	virtual void Fire(FVector direction) override;

private:
	TWeakObjectPtr<UProjectileSpellData> m_SpellData = nullptr;
};
