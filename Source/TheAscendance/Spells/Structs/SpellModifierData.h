// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheAscendance/Spells/Enums/SpellModifierType.h"
#include "SpellModifierData.generated.h"

// GENERIC MODIFIERS
USTRUCT(BlueprintType)
struct FGenericSpellModifier
{
	GENERATED_BODY()

	FGenericSpellModifier() : ModifierType(EGenericSpellModifierType::NONE) {};

	FGenericSpellModifier(EGenericSpellModifierType modifierType) : ModifierType(modifierType) {};

	EGenericSpellModifierType ModifierType = EGenericSpellModifierType::NONE;
};

USTRUCT(BlueprintType)
struct FApplyCasterEffectModifier : public FGenericSpellModifier
{
	GENERATED_BODY()

	FApplyCasterEffectModifier() : FGenericSpellModifier(EGenericSpellModifierType::APPLY_CASTER_EFFECT) {};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int EffectID = 0;
};

USTRUCT(BlueprintType)
struct FAreaOfEffectModifier : public FGenericSpellModifier
{
	GENERATED_BODY()

	FAreaOfEffectModifier() : FGenericSpellModifier(EGenericSpellModifierType::AOE) {};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Range = 0.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Damage = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ToolTip = "Damage is calculated using an interpolated value between 0 and the 'Range' value. 'DamageMinimum' clamps the minimum damage."))
	bool HasDamageFallOff = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "HasDamageFallOff == true", EditConditionHides))
	int DamageMinimum = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool DoesKnockback = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "DoesKnockback == true", EditConditionHides))
	float KnockbackStrength = 0.0f;
};
// GENERIC MODIFIERS

// RANGED SPELL MODIFIERS
USTRUCT(BlueprintType)
struct FRangedSpellModifier
{
	GENERATED_BODY()

	FRangedSpellModifier() : ModifierType(ERangedSpellModifierType::NONE) {};

	FRangedSpellModifier(ERangedSpellModifierType modifierType) : ModifierType(modifierType) {};

	ERangedSpellModifierType ModifierType = ERangedSpellModifierType::NONE;
};

USTRUCT(BlueprintType)
struct FKnockbackSpellModifier : public FRangedSpellModifier
{
	GENERATED_BODY()

	FKnockbackSpellModifier() : FRangedSpellModifier(ERangedSpellModifierType::KNOCKBACK) {};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float KnockbackStrength = 0.0f;
};
// RANGED SPELL MODIFIERS

// PROJECTILE SPELL MODIFIERS
USTRUCT(BlueprintType)
struct FProjectileSpellModifier
{
	GENERATED_BODY()

	FProjectileSpellModifier() : ModifierType(EProjectileSpellModifierType::NONE) {};

	FProjectileSpellModifier(EProjectileSpellModifierType modifierType) : ModifierType(modifierType) {};

	EProjectileSpellModifierType ModifierType = EProjectileSpellModifierType::NONE;
};

USTRUCT(BlueprintType)
struct FPenetrationSpellModifier : public FProjectileSpellModifier
{
	GENERATED_BODY()

	FPenetrationSpellModifier() : FProjectileSpellModifier(EProjectileSpellModifierType::PENETRATION) {};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int PenetrateLimit = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int DamageLossPerHit = 0;
};
// PROJECTILE SPELL MODIFIERS
