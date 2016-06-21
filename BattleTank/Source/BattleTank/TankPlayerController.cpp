// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GetControlledTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("Player: %s"), *GetControlledTank()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
	}
}

void ATankPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	AimAtCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector hitLocation;
	if (GetHitLocation(hitLocation))
	{

	}
}

bool ATankPlayerController::GetHitLocation(FVector& hitLocation) const
{
	return false;
}



