// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float);
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float maxDegsPerSecond = 20;
	UPROPERTY(EditAnywhere, Category = Setup)
		float maxElevation = 35;
	UPROPERTY(EditAnywhere, Category = Setup)
		float minElevation = 0;
	
};
