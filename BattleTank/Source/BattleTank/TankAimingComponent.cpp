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
	if (ammoLeft <= 0)
	{
		firingStatus = EFiringStatus::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - lastFireTime) < reloadTime)
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



EFiringStatus UTankAimingComponent::GetFiringStatus() const { return firingStatus; }
int32 UTankAimingComponent::GetAmmoLeft() const { return ammoLeft; }

void UTankAimingComponent::Initialise(UTankBarrel* myBarrel, UTankTurret* myTurret)
{
	barrel = myBarrel;
	turret = myTurret;
}

void UTankAimingComponent::Fire()
{
	if (!ensure(barrel) || !ensure(projectileBP) || firingStatus == EFiringStatus::OutOfAmmo || firingStatus == EFiringStatus::Reloading) { return; }
	
	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(projectileBP, barrel->GetSocketLocation(FName("Projectile")), barrel->GetSocketRotation(FName("Projectile")));
	projectile->LaunchProjectile(launchSpeed);
	lastFireTime = FPlatformTime::Seconds();
	ammoLeft--;
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

	if (FMath::Abs(targetRotation.Yaw) > 180)
	{
		turret->Rotate(180 - targetRotation.Yaw);
	}
	else
	{
		turret->Rotate(targetRotation.Yaw);
	}
}



