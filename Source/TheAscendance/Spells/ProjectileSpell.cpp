// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileSpell.h"
#include "TheAscendance/Core/CoreMacros.h"
#include "Interfaces/SpellCaster.h"
#include "Structs/SpellData.h"
#include "TheAscendance/Actors/Projectile/Projectile.h"

void UProjectileSpell::Init(USpellData* spellData, ISpellCaster* spellOwner)
{
	UBaseSpell::Init(spellData, spellOwner);

	if (spellData == nullptr || spellOwner == nullptr)
	{
		return;
	}

	if (UProjectileSpellData* data = Cast<UProjectileSpellData>(spellData))
	{
		m_SpellData = data;
	}
	else
	{
		LOG_ERROR("Tried to Init ProjectileSpellBase with invalid SpellData");
	}
}

bool UProjectileSpell::CastSpell()
{
	if (UBaseSpell::CastSpell() == false)
	{
		return false;
	}

	FVector unitDirection = GetSpellOwner()->GetCastStartForward();
	unitDirection.Normalize();

	Fire(unitDirection);

	return true;
}

void UProjectileSpell::Fire(FVector direction)
{
	UBaseSpell::Fire(direction);

	LOG_ONSCREEN(-1, 1.0f, FColor::Cyan, "Projectile: Fire");

	TObjectPtr<AActor> owner = m_SpellOwner->GetSpellOwner();

	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AProjectile* projectile = owner->GetWorld()->SpawnActor<AProjectile>(AProjectile::StaticClass(), m_SpellOwner->GetCastStartLocation(), FRotator::ZeroRotator, spawnParams);

	if (projectile == nullptr)
	{
		return;
	}

	projectile->Init(this, m_SpellData.Get());
	projectile->AddIgnoreActor(owner);

	//projectile->InitNiagara(spellData->spellNiagara);
	//projectile->SetRange(spellData->range);

	projectile->SetIsActive(true);
	projectile->ApplyForce(direction);
}
