// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

THEASCENDANCE_API DECLARE_LOG_CATEGORY_EXTERN(CoreLog, Log, All);

#define LOG_INFO(x, ...) UE_LOG(CoreLog, Log, TEXT(x), ##__VA_ARGS__)
#define LOG_WARNING(x, ...) UE_LOG(CoreLog, Warning, TEXT(x), ##__VA_ARGS__)
#define LOG_ERROR(x, ...) UE_LOG(CoreLog, Error, TEXT(x), ##__VA_ARGS__)
//  Example Usage (Same for all three)
// 	LOG_INFO("MACRO TEST %f", DeltaTime);

#define LOG_ONSCREEN(Index, Duration, Color, Format, ...) GEngine->AddOnScreenDebugMessage(Index, Duration, Color, FString::Printf(TEXT(Format), ##__VA_ARGS__));
//  Example Usage
// 	LOG_ONSCREEN(-1, 1.0f, FColor::Red, "MACRO TEST %f", DeltaTime);
