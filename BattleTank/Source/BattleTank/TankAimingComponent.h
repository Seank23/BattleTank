// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTankAimingComponent();
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankBarrel* myBarrel, UTankTurret* myTurret);
	UFUNCTION(BlueprintCallable, Category = "Fire")
		void Fire();

	void AimAt(FVector);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus firingStatus = EFiringStatus::Reloading;

private:
	void MoveTurretAndBarrel(FVector);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> projectileBP;

	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float launchSpeed = 5000;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float reloadTime = 3.0f;

	double lastFireTime = 0;
};
