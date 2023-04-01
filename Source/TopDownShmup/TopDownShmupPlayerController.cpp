// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "TopDownShmupPlayerController.h"
#include "TopDownShmup.h"
#include "TopDownShmupCharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

ATopDownShmupPlayerController::ATopDownShmupPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ATopDownShmupPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	UpdateMouseLook();
}

void ATopDownShmupPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();
	
	// Movement
	InputComponent->BindAxis("MoveForward", this, &ATopDownShmupPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATopDownShmupPlayerController::MoveRight);

	// Shooting
	InputComponent->BindAction("Fire", IE_Pressed, this, &ATopDownShmupPlayerController::OnStartFire);
	InputComponent->BindAction("Fire", IE_Released, this, &ATopDownShmupPlayerController::OnStopFire);
}

// Movement
void ATopDownShmupPlayerController::MoveForward(float Value)
{
	if(IgnoreMoveInput){return;}
	if (Value != 0.0f)
	{
		APawn* const OurPawn = GetPawn();
		if (OurPawn)
		{
			OurPawn->AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
		}
	}
}

void ATopDownShmupPlayerController::MoveRight(float Value)
{
	if(IgnoreMoveInput){return;}
	if (Value != 0.0f)
	{
		APawn* const OurPawn = GetPawn();
		if (OurPawn)
		{
			OurPawn->AddMovementInput(FVector(0.0f, 1.0f, 0.0f), Value);
		}
	}
}

// Mouselook
void ATopDownShmupPlayerController::UpdateMouseLook()
{
	if(IgnoreLookInput){return;}
	APawn* const OurPawn = GetPawn();
	if (OurPawn)
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		if (Hit.bBlockingHit)
		{
			// We hit something, look there
			FVector rotation = (Hit.ImpactPoint - OurPawn->GetActorLocation());
			rotation.Z = 0.0f;
			rotation.Normalize();
			FRotator trueRotation = rotation.Rotation();
			OurPawn->SetActorRotation(trueRotation);
		}
	}
}


// Firing (Trigger)
void ATopDownShmupPlayerController::OnStartFire()
{
	APawn* OurPawn = GetPawn();
	if (OurPawn)
	{
		ATopDownShmupCharacter *MyCharacter = Cast<ATopDownShmupCharacter>(OurPawn);
		MyCharacter->OnStartFire();
	}
}

void ATopDownShmupPlayerController::OnStopFire()
{
	APawn* OurPawn = GetPawn();
	if (OurPawn)
	{
		ATopDownShmupCharacter *MyCharacter = Cast<ATopDownShmupCharacter>(OurPawn);
		MyCharacter->OnStopFire();
	}
}
