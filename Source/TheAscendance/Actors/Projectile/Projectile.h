// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UProjectileMovementComponent;
class UProjectileSpellData;
class ISpell;

UCLASS()
class THEASCENDANCE_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	void Init(ISpell* spell, UProjectileSpellData* spellData);
	void AddIgnoreActor(AActor* toIgnore);
	void SetIsActive(bool isActive);
	void ApplyForce(FVector unitDirection);

	void HandleStaticActorHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit);
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> m_StaticMeshComponent;
	UPROPERTY()
	TObjectPtr<USphereComponent> m_Collider;
	UPROPERTY()
	TObjectPtr<UProjectileMovementComponent> m_MovementComponent;

	UPROPERTY()
	TScriptInterface<ISpell> m_Spell;

	TWeakObjectPtr<UProjectileSpellData> m_SpellData;

	TWeakObjectPtr<AActor> m_IgnoredOwner = nullptr;

	FVector m_StartPos = FVector::ZeroVector;
	float m_MaxTravelDistance = 0.0f;

	bool m_IsActive = false;
};
