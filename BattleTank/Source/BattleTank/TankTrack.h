// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float throttle);
	UPROPERTY(EditDefaultsOnly)
		float maxDrivingForce = 100000;

private:
	UTankTrack();
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit);

	void ApplySidewaysForce();
	void DriveTrack();

	float currentThrottle = 0;
};
