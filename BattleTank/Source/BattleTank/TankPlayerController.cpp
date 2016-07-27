// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetControlledTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
	}

	auto aimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (aimingComponent)
	{
		FoundAimingComponent(aimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Aiming Component not found"));
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
	if (!ensure(GetControlledTank())) { return; }

	FVector hitLocation;
	if (GetHitLocation(hitLocation))
	{
		GetControlledTank()->AimAt(hitLocation);
	}
}

bool ATankPlayerController::GetHitLocation(FVector& hitLocation) const
{
	int32 viewportSizeX, viewportSizeY;
	FVector cameraLocation, lookDirection;

	GetViewportSize(viewportSizeX, viewportSizeY);
	FVector2D screenLocation = FVector2D(viewportSizeX * crosshairX, viewportSizeY * crosshairY);

	if (DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraLocation, lookDirection))
	{
		FHitResult hit;
		FVector rayEnd = cameraLocation + (lookDirection * rayDistance);

		if (GetWorld()->LineTraceSingleByChannel(hit, cameraLocation, rayEnd, ECollisionChannel::ECC_Visibility))
		{
			hitLocation = hit.Location;
			return true;
		}
	}
	return false;
}



