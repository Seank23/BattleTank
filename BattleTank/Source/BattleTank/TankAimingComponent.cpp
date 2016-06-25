// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}



void UTankAimingComponent::SetBarrelReference(UTankBarrel* barrel) { this->barrel = barrel; }

void UTankAimingComponent::AimAt(FVector aimLocation, float launchSpeed)
{
	if (!barrel) { return; }

	FVector outLaunchVelocity;
	FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(this, outLaunchVelocity, startLocation, aimLocation, launchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		FVector aimDirection = outLaunchVelocity.GetSafeNormal();
		MoveBarrel(aimDirection);
	}
}

void UTankAimingComponent::MoveBarrel(FVector aimDirection)
{
	FRotator barrelRotation = barrel->GetForwardVector().Rotation();
	FRotator targetRotation = aimDirection.Rotation() - barrelRotation;
	UE_LOG(LogTemp,Warning, TEXT("Rotation this frame: %f"), targetRotation.Pitch)
	barrel->Elevate(targetRotation.Pitch);
}

