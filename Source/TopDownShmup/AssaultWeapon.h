// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "AssaultWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHMUP_API AAssaultWeapon : public AWeapon
{
	GENERATED_BODY()
	
public:
	// Damage
	UPROPERTY(EditAnywhere)
	float ARDamage = 2;
	// Firing
	float FireRate = 0.5f;
	float WeaponRange = 10000.0f;
	UPROPERTY(EditDefaultsOnly, Category=Effects)
	UParticleSystem* HitEffect;
	FTimerHandle ShotTimer;
	// Overrides
	virtual void OnStartFire() override;
	virtual void OnStopFire() override;
	
protected:
	// Firing
	virtual void WeaponTrace();
};
