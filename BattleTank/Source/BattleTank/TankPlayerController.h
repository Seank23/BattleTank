// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

	ATank* GetControlledTank() const;
	void AimAtCrosshair();
	bool GetHitLocation(FVector&) const;

	UPROPERTY(EditAnywhere)
		float crosshairX = 0.5;
	UPROPERTY(EditAnywhere)
		float crosshairY = 0.3333;
	UPROPERTY(EditAnywhere)
		int32 rayDistance = 1000000;
};
