// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	virtual float TakeDamage(float damageAmount, struct FDamageEvent const &damageEvent, class AController* eventInstigator, AActor* damageSource) override;

	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPercent();

	FTankDelegate OnDeath;

private:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Health")
		int16 maxHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Health")
		int16 currentHealth;
};
