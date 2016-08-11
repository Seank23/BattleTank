// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float acceptanceRadius = 4000;

private:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

	virtual void SetPawn(APawn* pawn) override;

	UFUNCTION()
		void OnAIDeath();

	ATank* myTank = nullptr;
};
