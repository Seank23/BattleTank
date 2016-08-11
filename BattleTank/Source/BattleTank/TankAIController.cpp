// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	auto playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (ensure(playerTank && GetPawn()))
	{
		MoveToActor(playerTank, acceptanceRadius);

		auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		aimingComponent->AimAt(playerTank->GetActorLocation());

		if(aimingComponent->GetFiringStatus() == EFiringStatus::Locked)
			aimingComponent->Fire();
	}
}



void ATankAIController::SetPawn(APawn* pawn)
{
	Super::SetPawn(pawn);
	
	if (pawn)
	{
		myTank = Cast<ATank>(pawn);
		if (!ensure(myTank)) { return; }

		myTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnAIDeath);
	}
}

void ATankAIController::OnAIDeath()
{
	myTank->DetachFromControllerPendingDestroy();
}


