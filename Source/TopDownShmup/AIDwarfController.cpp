// Fill out your copyright notice in the Description page of Project Settings.


#include "AIDwarfController.h"

#include "DwarfCharacter.h"
#include "HairStrandsInterface.h"
#include "Kismet/GameplayStatics.h"

void AAIDwarfController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	MyDwarf = InPawn;
}

void AAIDwarfController::OnUnPossess()
{
	Super::OnUnPossess();
	SetCurrentState(EDwarfState::EDead);
	SetActorTickEnabled(false);
}

void AAIDwarfController::BeginPlay()
{
	Super::BeginPlay();
	SetCurrentState(EDwarfState::EStart);
}

void AAIDwarfController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Move completed!"), true);
	Cast<ADwarfCharacter>(MyDwarf)->StartAttack();
	SetCurrentState(EDwarfState::EAttacking);
}

void AAIDwarfController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Player = Cast<ATopDownShmupCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (GetCurrent() == EDwarfState::EStart)
	{
		SetCurrentState(EDwarfState::EChasing);
	}
	
	if (GetCurrent() == EDwarfState::EChasing)
	{
		MoveToActor(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	}

	if (GetCurrent() == EDwarfState::EAttacking)
	{
		if (MyDwarf->GetDistanceTo(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)) > AttkDist)
		{
			SetCurrentState(EDwarfState::EChasing);
			Cast<ADwarfCharacter>(MyDwarf)->StopAttack();
		}
	}

	if (Player->CanBeDamaged() == false)
	{
		SetCurrentState(EDwarfState::EDead);
		Cast<ADwarfCharacter>(MyDwarf)->StopAttack();
	}
}

// State machine
EDwarfState AAIDwarfController::GetCurrent() const
{
	return DwarfState;
}

void AAIDwarfController::SetCurrentState(EDwarfState NewState)
{
	DwarfState = NewState;
}
