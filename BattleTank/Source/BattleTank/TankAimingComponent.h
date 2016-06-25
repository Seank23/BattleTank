// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTankAimingComponent();
	
	void SetBarrelReference(UTankBarrel*);
	void SetTurretReference(UTankTurret*);
	void AimAt(FVector, float);

private:
	void MoveTurretAndBarrel(FVector);

	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;
};
