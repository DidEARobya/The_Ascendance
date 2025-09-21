// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellBase.h"
#include "ProjectileSpellBase.generated.h"

/**
 * 
 */
UCLASS()
class THEASCENDANCE_API UProjectileSpellBase : public USpellBase
{
	GENERATED_BODY()
	
public:
	//virtual void Init() override;
	//virtual bool CastSpell() override;

	//virtual void Update(float deltaTime) override;
	//virtual void ProcessHit(AActor* target, FVector location) override;

	virtual void Fire(FVector direction) override;
};
