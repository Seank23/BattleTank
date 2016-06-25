// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::Rotate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp(relativeSpeed, -1.0f, 1.0f);
	float rotationChange = relativeSpeed * maxDegsPerSecond * GetWorld()->DeltaTimeSeconds;
	float newRotation = RelativeRotation.Yaw + rotationChange;

	SetRelativeRotation(FRotator(0, newRotation, 0));
}


