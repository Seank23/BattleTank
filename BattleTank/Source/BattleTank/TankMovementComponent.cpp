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
	if (!leftTrack || !rightTrack) { return; }
	leftTrack->SetThrottle(offset);
	rightTrack->SetThrottle(offset);
}

void UTankMovementComponent::IntendedTurnRight(float offset)
{
	if (!leftTrack || !rightTrack) { return; }
	leftTrack->SetThrottle(offset);
	rightTrack->SetThrottle(-offset);
}


