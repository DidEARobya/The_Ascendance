// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TheAscendance/Spells/Interfaces/Spell.h"
#include "TheAscendance/Core/CoreMacros.h"
#include "SpellDecorator.generated.h"

class ISpell;
class ISpellCaster;

UCLASS()
class THEASCENDANCE_API USpellDecorator : public UObject, public ISpell
{
	GENERATED_BODY()
	
public:
	void Decorate(ISpell* decorator);

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
	TScriptInterface<ISpell> m_DecoratedSpell = nullptr;
};
