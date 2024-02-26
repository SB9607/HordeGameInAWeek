// Fill out your copyright notice in the Description page of Project Settings.
#include "HoardGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"

void AHoardGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AHoardGameMode::CheckRemainingEnemies()
{
	if (remainingEnemies == 0)
	{
		OnRespawnEnemies.Broadcast();
		roundNumber++;
	}
}

void AHoardGameMode::IncreasePlayerEXPAndPoints(float EXP, float Points)
{
	OnIncreasePlayerEXPAndPoints.Broadcast(EXP, Points);
}
