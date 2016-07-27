// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class AProjectile;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Fire")
		void Fire();

	void AimAt(FVector);

protected:
	UPROPERTY(BlueprintReadOnly)
		UTankAimingComponent* aimingComponent = nullptr;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> projectileBP;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float launchSpeed = 5000;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float reloadTime = 3.0f;

	double lastFireTime = 0;
	UTankBarrel* localBarrel = nullptr;
};
