// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* lTrack, UTankTrack* rTrack)
{
	leftTrack = lTrack;
	rightTrack = rTrack;
}

void UTankMovementComponent::IntendedForwardMove(float offset)
{
	if (!ensure(leftTrack) || !ensure(rightTrack)) { return; }

	leftTrack->SetThrottle(offset);
	rightTrack->SetThrottle(offset);
}

void UTankMovementComponent::IntendedTurnRight(float offset)
{
	if (!ensure(leftTrack) || !ensure(rightTrack)) { return; }

	leftTrack->SetThrottle(offset);
	rightTrack->SetThrottle(-offset);
}

void UTankMovementComponent::RequestDirectMove(const FVector& moveVelocity, bool bForceMaxSpeed)
{
	FVector tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector targetVelocity = moveVelocity.GetSafeNormal();

	//float targetForwardMovement = FVector::DotProduct(tankForward, targetVelocity);

	float targetForwardMovement = ((tankForward.X * targetVelocity.X) + (tankForward.Y * targetVelocity.Y) + (tankForward.Z * targetVelocity.Z))
			/ (sqrt(pow(tankForward.X, 2) + pow(tankForward.Y, 2) + pow(tankForward.Z, 2)) * sqrt(pow(targetVelocity.X, 2) + pow(targetVelocity.Y, 2) + pow(targetVelocity.Z, 2)));

	float targetRightMovement = FVector::CrossProduct(tankForward, targetVelocity).Z;

	IntendedForwardMove(targetForwardMovement);
	IntendedTurnRight(targetRightMovement);
}


