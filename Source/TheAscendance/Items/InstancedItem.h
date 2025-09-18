// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "InstancedItem.generated.h"

UCLASS()
class THEASCENDANCE_API AInstancedItem : public AItem
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditInstanceOnly, meta = (DisplayName = "Instance ID"))
	int m_InstanceID = 0;
};
