// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	HAND UMETA(DisplayName = "Hand"),

	SWORD UMETA(DisplayName = "Sword"),
	//STAFF UMETA(DisplayName = "Staff"),

	MAX UMETA(Hidden)
};
