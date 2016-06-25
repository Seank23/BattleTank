// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp(relativeSpeed, -1.0f, 1.0f);
	float elevationChange = relativeSpeed * maxDegsPerSecond * GetWorld()->DeltaTimeSeconds;
	float newElevation = FMath::Clamp(RelativeRotation.Pitch + elevationChange, minElevation, maxElevation);

	SetRelativeRotation(FRotator(newElevation, 0, 0));
}


