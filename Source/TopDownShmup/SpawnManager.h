// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

UCLASS()
class TOPDOWNSHMUP_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnManager();

	UPROPERTY(EditAnywhere)
	TArray<ATargetPoint*> TargetPoints;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ACharacter> SpawnChar;
	UPROPERTY(EditAnywhere)
	float MinSTime = 1.0f;
	UPROPERTY(EditAnywhere)
	float MaxSTime = 10.0f;

	virtual void SpawnCharacter();

	FTimerHandle SpawnTimer;
	virtual void SpawnRepeater();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
