// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Tank.h"



void ATank::AimAt(FVector hitLocation)
{
	if (!ensure(aimingComponent)) { return; }
	aimingComponent->AimAt(hitLocation, launchSpeed);
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - lastFireTime) > reloadTime;
	if (!ensure(localBarrel) || isReloaded) { return; }
	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(projectileBP, localBarrel->GetSocketLocation(FName("Projectile")), localBarrel->GetSocketRotation(FName("Projectile")));
	projectile->LaunchProjectile(launchSpeed);
	lastFireTime = FPlatformTime::Seconds();
}

