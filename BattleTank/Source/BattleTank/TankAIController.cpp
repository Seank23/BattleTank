// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	if (GetPlayerTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("Player tank found: %s"), *GetPlayerTank()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player tank not found"));
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}


