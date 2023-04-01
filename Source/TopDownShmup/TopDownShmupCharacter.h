// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Weapon.h"
#include "TopDownShmupCharacter.generated.h"

UCLASS(Blueprintable)
class ATopDownShmupCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;


public:
	ATopDownShmupCharacter();
	// Health n stuff
	UPROPERTY(EditAnywhere)
	float MyHealth = 100;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	// Weapon
	UPROPERTY(EditAnywhere, Category=Weapon)
	TSubclassOf<AWeapon> WeaponClass;
	// Firing (passthrough)
	virtual void OnStartFire();
	virtual void OnStopFire();
	// Overrides
	virtual void BeginPlay() override;
	// Take damage
	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	bool Dead = false;
	// Dying
	FTimerHandle DeathTimer;
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* DeathAnim;
	virtual void Die();
	
private:
	// Weapon
	AWeapon* MyWeapon;
};

