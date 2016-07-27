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

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTankAimingComponent();
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankBarrel* myBarrel, UTankTurret* myTurret);

	void AimAt(FVector, float);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus firingStatus = EFiringStatus::Reloading;

private:
	void MoveTurretAndBarrel(FVector);

	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;
};
