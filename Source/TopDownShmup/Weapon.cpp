
// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Firing
void AWeapon::OnStartFire()
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Start fire"), true);
	// Audio
	FireAC = PlayWeaponSound(FireLoopSound);
	// FX
	MuzzleFXC = PlayMuzzleFX(MuzzleFX);
}

void AWeapon::OnStopFire()
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Stop fire"), true);
	// Audio
	FireAC->Stop();
	MuzzleFXC->DeactivateSystem();
	PlayWeaponSound(FireFinishSound);
}

// Audio
UAudioComponent* AWeapon::PlayWeaponSound(USoundCue* Sound)
{
	UAudioComponent* AC = nullptr;
	if (Sound)
	{
		AC = UGameplayStatics::SpawnSoundAttached(Sound, RootComponent);
	}
	return AC;
}

// FX
UParticleSystemComponent* AWeapon::PlayMuzzleFX(UParticleSystem* FX)
{
	UParticleSystemComponent* rFX = nullptr;
	if (FX)
	{
		rFX = UGameplayStatics::SpawnEmitterAttached(FX, RootComponent, TEXT("MuzzleFlashSocket"));
	}
	return rFX;
}

