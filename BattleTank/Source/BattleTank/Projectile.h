// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();
	virtual void BeginPlay() override;
	void LaunchProjectile(float);

protected:
	UProjectileMovementComponent* projectileMovementComponent = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Setup")
		UStaticMeshComponent* collisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Setup")
		UParticleSystemComponent* launchBlast = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Setup")
		UParticleSystemComponent* impactBlast = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Setup")
		URadialForceComponent* explosionForce = nullptr;

private:
	UFUNCTION()
		void OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit);

	void OnTimerExpire();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float destroyDelay = 5.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float projectileDamage = 20.0f;
};
