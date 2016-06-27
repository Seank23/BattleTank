// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	tankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}



void ATank::SetBarrelReference(UTankBarrel* barrel) { tankAimingComponent->SetBarrelReference(barrel); localBarrel = barrel; }
void ATank::SetTurretReference(UTankTurret* turret) { tankAimingComponent->SetTurretReference(turret); }

void ATank::AimAt(FVector hitLocation)
{
	tankAimingComponent->AimAt(hitLocation, launchSpeed);
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - lastFireTime) > reloadTime;
	if (!localBarrel || !isReloaded) { return; }
	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(projectileBP, localBarrel->GetSocketLocation(FName("Projectile")), localBarrel->GetSocketRotation(FName("Projectile")));
	projectile->LaunchProjectile(launchSpeed);
	lastFireTime = FPlatformTime::Seconds();
}

