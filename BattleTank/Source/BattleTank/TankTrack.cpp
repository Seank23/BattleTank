// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}



void UTankTrack::OnHit(UPrimitiveComponent * hitComponent, AActor * otherActor, UPrimitiveComponent * otherComp, FVector normalImpulse, const FHitResult & hit)
{
	DriveTrack();
	ApplySidewaysForce();
	currentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce()
{
	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	float slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	FVector correctionAcceleration = -slippageSpeed / GetWorld()->GetDeltaSeconds() * GetRightVector();
	FVector slidewaysFriction = correctionAcceleration * tankRoot->GetMass() / 2;

	tankRoot->AddForce(slidewaysFriction);
}

void UTankTrack::SetThrottle(float throttle)
{
	currentThrottle = FMath::Clamp<float>(currentThrottle + throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	FVector forceApplied = GetForwardVector() * currentThrottle * maxDrivingForce;
	UPrimitiveComponent* tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	tankRoot->AddForceAtLocation(forceApplied, GetComponentLocation());
}


