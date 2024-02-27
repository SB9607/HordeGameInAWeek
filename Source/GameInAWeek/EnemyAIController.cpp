// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	//Setting the player pawn reference
	PlayerCharRef = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

}

void AEnemyAIController::Tick(float DeltaTime)
{

}
