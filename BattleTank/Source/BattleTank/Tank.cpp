// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"

void ATank::BeginPlay()
{
	Super::BeginPlay();

	currentHealth = maxHealth;
}

float ATank::TakeDamage(float damageAmount, struct FDamageEvent const &damageEvent, class AController* eventInstigator, AActor* damageSource)
{
	int16 damageInt = FPlatformMath::RoundToInt(damageAmount);
	int16 damageToApply = FMath::Clamp(damageInt, *new int16(0), currentHealth);

	currentHealth -= damageToApply;

	if (currentHealth <= 0)
	{
		OnDeath.Broadcast();
	}

	return damageToApply;
}

float ATank::GetHealthPercent()
{
	return (float)currentHealth / (float)maxHealth;
}
