// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "DwarfCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHMUP_API ADwarfCharacter : public AEnemyCharacter
{
	GENERATED_BODY()
	
public:
	ADwarfCharacter();
	// Health n stuff
	UPROPERTY(EditAnywhere)
	float MyHealth = 20;
	// Damage
	UPROPERTY(EditAnywhere)
	float HammerDamage = 10;

	// Attack
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* AttackAnim;
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* DeathAnim;
	virtual void StartAttack();
	virtual void StopAttack();
	virtual void Hit();
	FTimerHandle HitTimer;
	FTimerHandle DeathTimer;
	virtual void Die();

	// Take damage
	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
