// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	ATank* playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ATank* myTank = Cast<ATank>(GetPawn());

	if (ensure(playerTank))
	{
		MoveToActor(playerTank, acceptanceRadius);

		myTank->AimAt(playerTank->GetActorLocation());
		myTank->Fire();
	}
}


