// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* aimingComponent);

private:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

	virtual void SetPawn(APawn* pawn) override;

	UFUNCTION()
		void OnPlayerDeath();
	
	void AimAtCrosshair();
	bool GetHitLocation(FVector&) const;

	UPROPERTY(EditDefaultsOnly)
		float crosshairX = 0.5;
	UPROPERTY(EditDefaultsOnly)
		float crosshairY = 0.3333;
	UPROPERTY(EditDefaultsOnly)
		int32 rayDistance = 1000000;
};
