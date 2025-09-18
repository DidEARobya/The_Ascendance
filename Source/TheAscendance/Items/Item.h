// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class UStaticMeshComponent;
class UStaticMesh;
struct FItemData;

UCLASS()
class THEASCENDANCE_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	void Init(FItemData* itemData);
	void SetStaticMesh();

private:
	UPROPERTY();
	TSoftObjectPtr<UStaticMesh> m_Mesh = nullptr;
	UPROPERTY(EditInstanceOnly, meta = (DisplayName = "Static Mesh Component"));
	TObjectPtr<UStaticMeshComponent> m_MeshComponent = nullptr;

	TSharedPtr<FItemData> m_ItemData = nullptr;
};
