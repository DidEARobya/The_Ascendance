// Fill out your copyright notice in the Description page of Project Settings.


#include "AOESpellDecorator.h"
#include "TheAscendance/Core/CoreFunctionLibrary.h"
#include "TheAscendance/Spells/Interfaces/SpellCaster.h"
#include "TheAscendance/Characters/Interfaces/Susceptible.h"

#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Character.h"

void UAOESpellDecorator::OnHit(AActor* hitActor, FVector spellHitLocation)
{
	m_DecoratedSpell->OnHit(hitActor, spellHitLocation);

	if (m_AoeData == nullptr)
	{
		return;
	}

	int damage = 0;
	m_DecoratedSpell->ProcessHitDamage(damage, hitActor->GetActorLocation(), spellHitLocation);
	m_DecoratedSpell->DealDamage(hitActor, damage);

	AActor* owner = GetSpellOwner()->GetSpellOwner();

	TArray<TEnumAsByte<EObjectTypeQuery>> types;
	types.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));
	types.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	TArray<TObjectPtr<AActor>> ignore;
	//ignore.Add(owner);

	TArray<AActor*> targets;

	UCoreFunctionLibrary::DrawDebugSphere(spellHitLocation, m_AoeData->Range, 16, FColor::Yellow);

	if (UKismetSystemLibrary::SphereOverlapActors(owner->GetWorld(), spellHitLocation, m_AoeData->Range, types, NULL, ignore, targets))
	{
		for (TObjectPtr<AActor> a : targets)
		{
			m_DecoratedSpell->OnHit(a, spellHitLocation);
		}
	}
}

void UAOESpellDecorator::ProcessHit(FVector spellHitLocation)
{
	if (m_AoeData->DoesKnockback == false)
	{
		m_DecoratedSpell->ProcessHit(spellHitLocation);
		return;
	}

	for (AActor* actor : GetHitActors())
	{
		FVector knockbackDirection = actor->GetActorLocation() - spellHitLocation;
		knockbackDirection.Normalize();
		knockbackDirection.Z = FMath::Max(knockbackDirection.Z, 0.5f);

		float distance = FVector::Distance(actor->GetActorLocation(), spellHitLocation);
		float normalizedDistance = distance / m_AoeData->Range;

		float knockbackStrength = m_AoeData->KnockbackStrength - (m_AoeData->KnockbackStrength - 0.0f) * normalizedDistance * normalizedDistance;
		knockbackStrength = FMath::Clamp(knockbackStrength, 0.0f, m_AoeData->KnockbackStrength);

		if (ACharacter* character = Cast<ACharacter>(actor))
		{
			character->LaunchCharacter(knockbackDirection * knockbackStrength, true, true);
			continue;
		}

		if (UPrimitiveComponent* primitiveComponent = actor->FindComponentByClass<UPrimitiveComponent>())
		{
			if (primitiveComponent->IsSimulatingPhysics() == false)
			{
				continue;
			}

			primitiveComponent->AddImpulse(knockbackDirection * knockbackStrength, NAME_None, true);
		}
	}

	m_DecoratedSpell->ProcessHit(spellHitLocation);
}

void UAOESpellDecorator::ProcessHitDamage(int& damage, FVector targetLocation, FVector hitLocation)
{
	if (m_AoeData->HasDamageFallOff == false)
	{
		damage += m_AoeData->Damage;
		return;
	}

	float distance = FVector::Distance(targetLocation, hitLocation);

	float normalizedDistance = distance / m_AoeData->Range;
	float damageWithFalloff = m_AoeData->Damage - (m_AoeData->Damage - m_AoeData->DamageMinimum) * normalizedDistance * normalizedDistance;

	damageWithFalloff = FMath::Clamp(damageWithFalloff, m_AoeData->DamageMinimum, m_AoeData->Damage);

	damage += damageWithFalloff;
}

bool UAOESpellDecorator::CastSpell()
{
	if (m_DecoratedSpell == nullptr)
	{
		LOG_ERROR("AOESpellDecorator has no decorated spell");
		return false;
	}

	FVector unitDirection = m_DecoratedSpell->GetSpellOwner()->GetCastStartForward();
	unitDirection.Normalize();

	Fire(unitDirection);

	return true;
}

void UAOESpellDecorator::Fire(FVector direction)
{
	m_DecoratedSpell->Fire(direction);

	LOG_ONSCREEN(-1, 1.0f, FColor::Cyan, "AOE Decorator: Fire");
}
