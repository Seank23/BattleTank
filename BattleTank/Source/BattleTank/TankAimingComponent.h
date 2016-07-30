// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
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
		int32 GetAmmoLeft() const;
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankBarrel* myBarrel, UTankTurret* myTurret);
	UFUNCTION(BlueprintCallable, Category = "Fire")
		void Fire();

	void AimAt(FVector);

	EFiringStatus GetFiringStatus() const;

	

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus firingStatus = EFiringStatus::Reloading;

private:
	virtual void BeginPlay() override;
	virtual void TickComponent(float deltaTime, enum ELevelTick tickType, FActorComponentTickFunction* thisTickFunction) override;

	bool IsBarrelMoving();
	void MoveTurretAndBarrel(FVector);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> projectileBP;

	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float launchSpeed = 5000;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float reloadTime = 3.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		int32 ammoLeft = 3;

	double lastFireTime = 0;

	FVector aimDirection;
};
