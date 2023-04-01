// Fill out your copyright notice in the Description page of Project Settings.


#include "AssaultWeapon.h"

#include "DwarfCharacter.h"
#include "TextFilterExpressionEvaluator.h"
#include "Kismet/GameplayStatics.h"

// Firing
void AAssaultWeapon::OnStartFire()
{
	Super::OnStartFire();
	GetWorld()->GetTimerManager().SetTimer(ShotTimer, this, &AAssaultWeapon::WeaponTrace, FireRate, true);
}

void AAssaultWeapon::OnStopFire()
{
	Super::OnStopFire();
	GetWorld()->GetTimerManager().ClearTimer(ShotTimer);
}

void AAssaultWeapon::WeaponTrace()
{
	static FName WeaponFireTag = FName(TEXT("WeaponTrace"));
	static FName MuzzleSocket = FName(TEXT("MuzzleFlashSocket"));
	// Start from the muzzle's position
	FVector StartPos = WeaponMesh->GetSocketLocation(MuzzleSocket);
	// Get forward vector of MyPawn
	FVector Forward = MyPawn->GetActorForwardVector();
	// Calculate end position
	FVector EndPos = StartPos + Forward * WeaponRange;
	// Perform line trace to retrieve hit info
	FCollisionQueryParams TraceParams(WeaponFireTag, true, GetInstigator());
	// This fires the ray and checks against all objects w/ collision
	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByObjectType(Hit, StartPos, EndPos,FCollisionObjectQueryParams::AllObjects, TraceParams);
	// Did this hit anything?
	if (Hit.bBlockingHit)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, Hit.Location);
		ADwarfCharacter* Dwarf = Cast<ADwarfCharacter>(Hit.GetActor());
		if (Dwarf)
		{
			Dwarf->TakeDamage(ARDamage, FDamageEvent(), GetInstigatorController(), this);
		}
	}
}
