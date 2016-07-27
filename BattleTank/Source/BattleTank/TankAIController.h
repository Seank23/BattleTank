// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class UTank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
		float acceptanceRadius = 2000;

private:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
};
