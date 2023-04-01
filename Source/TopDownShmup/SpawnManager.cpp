// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManager.h"

#include "DwarfCharacter.h"

// Sets default values
ASpawnManager::ASpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &ASpawnManager::SpawnRepeater, MinSTime, false);
}

// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Spawn a Char
void ASpawnManager::SpawnCharacter()
{
	UWorld* World = GetWorld();
	if (World)
	{
		// Set the parameters
		FVector SpawnLocation = TargetPoints[FMath::RandRange(0, TargetPoints.Num() - 1)]->GetActorLocation();
		FRotator SpawnRotation(0.0f, 0.0f, 0.0f);
		// Spawn the Char
		ADwarfCharacter* Dwarf = World->SpawnActor<ADwarfCharacter>(SpawnChar, SpawnLocation, SpawnRotation);
		Dwarf->SpawnDefaultController();
	}
}

// Spawn a char every [rand] seconds
void ASpawnManager::SpawnRepeater()
{
	GetWorld()->GetTimerManager().ClearTimer(SpawnTimer); // Just in case
	SpawnCharacter();
	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &ASpawnManager::SpawnRepeater, FMath::RandRange(MinSTime, MaxSTime), false);
}

