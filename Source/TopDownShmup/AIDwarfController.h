// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIEnemyController.h"
#include "TopDownShmupCharacter.h"
#include "AIDwarfController.generated.h"

/**
 * 
 */

enum class EDwarfState : short
{
	EStart, EChasing, EAttacking, EDead, EUnknown
};

UCLASS()
class TOPDOWNSHMUP_API AAIDwarfController : public AAIEnemyController
{
	GENERATED_BODY()
public:
	APawn* MyDwarf;
	ATopDownShmupCharacter* Player;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	virtual void BeginPlay() override;
	virtual void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) override;

	// Get/set for state machine
	EDwarfState GetCurrent() const;
	void SetCurrentState(EDwarfState NewState);
	
private:
	EDwarfState DwarfState = EDwarfState::EUnknown;
	float AttkDist = 150.0f;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
