// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	lastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction)
{
	Super::TickComponent(deltaTime, tickType, thisTickFunction);

	if ((FPlatformTime::Seconds() - lastFireTime) < reloadTime)
	{
		firingStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		firingStatus = EFiringStatus::Aiming;
	}
	else
	{
		firingStatus = EFiringStatus::Locked;
	}
}



void UTankAimingComponent::Initialise(UTankBarrel* myBarrel, UTankTurret* myTurret)
{
	barrel = myBarrel;
	turret = myTurret;
}

void UTankAimingComponent::Fire()
{
	if (firingStatus != EFiringStatus::Reloading)
	{
		if (!ensure(barrel) || !ensure(projectileBP)) { return; }

		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(projectileBP, barrel->GetSocketLocation(FName("Projectile")), barrel->GetSocketRotation(FName("Projectile")));
		projectile->LaunchProjectile(launchSpeed);
		lastFireTime = FPlatformTime::Seconds();
	}
}

void UTankAimingComponent::AimAt(FVector aimLocation)
{
	if (!ensure(barrel) || !ensure(turret)) { return; }

	FVector outLaunchVelocity;
	FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(this, outLaunchVelocity, startLocation, aimLocation, launchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		aimDirection = outLaunchVelocity.GetSafeNormal();
		MoveTurretAndBarrel(aimDirection);
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(barrel)) { return false; }

	return !barrel->GetForwardVector().Equals(aimDirection, 0.1f);
}

void UTankAimingComponent::MoveTurretAndBarrel(FVector aimDirection)
{
	if (!ensure(barrel) || !ensure(turret)) { return; }

	FRotator barrelRotation = barrel->GetForwardVector().Rotation();
	FRotator targetRotation = aimDirection.Rotation() - barrelRotation;
	barrel->Elevate(targetRotation.Pitch);
	turret->Rotate(targetRotation.Yaw);
}



