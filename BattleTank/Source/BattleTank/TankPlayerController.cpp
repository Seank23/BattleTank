// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetPawn())
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));

	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(aimingComponent)) { return; }
	FoundAimingComponent(aimingComponent);
}

void ATankPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	AimAtCrosshair();
}



void ATankPlayerController::SetPawn(APawn* pawn)
{
	Super::SetPawn(pawn);

	if (pawn)
	{
		ATank* myTank = Cast<ATank>(pawn);
		if (!ensure(myTank)) { return; }

		myTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPlayerDeath);
	}
}

void ATankPlayerController::OnPlayerDeath()
{
	StartSpectatingOnly();
}

void ATankPlayerController::AimAtCrosshair()
{
	if (!GetPawn()) { return; }
	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(aimingComponent)) { return; }

	FVector hitLocation;
	if (GetHitLocation(hitLocation))
	{
		aimingComponent->AimAt(hitLocation);
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



