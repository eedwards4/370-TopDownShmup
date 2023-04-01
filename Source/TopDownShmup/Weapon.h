// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "Weapon.generated.h"

UCLASS()
class TOPDOWNSHMUP_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	// Mesh
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category=Weapon)
	USkeletalMeshComponent* WeaponMesh;

	// Firing
	virtual void OnStartFire();
	virtual void OnStopFire();

	// Audio
	UPROPERTY(EditDefaultsOnly, Category=Sound)
	USoundCue* FireLoopSound;
	UPROPERTY(EditDefaultsOnly, Category=Sound)
	USoundCue* FireFinishSound;

	// FX
	UPROPERTY(EditDefaultsOnly, Category=Effects)
	UParticleSystem* MuzzleFX;

	// Owner
	APawn* MyPawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Audio
	UPROPERTY(Transient)
	UAudioComponent* FireAC;
	// Audio (Functions)
	UAudioComponent* PlayWeaponSound(USoundCue* Sound);

	// FX
	UPROPERTY(Transient)
	UParticleSystemComponent* MuzzleFXC;
	// FX (Functions)
	UParticleSystemComponent* PlayMuzzleFX(UParticleSystem* FX);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
