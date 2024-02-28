// Fill out your copyright notice in the Description page of Project Settings.
#include "HoardGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
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


void AHoardGameMode::IsPlayerLevelling(bool isPlayerLevelling)
{
	if (isPlayerLevelling)
	{

		//ShowLevelUpHUD();
	}
	else
	{
		InitialisePlayerHUD();
	}
	OnIsLevelling.Broadcast(isPlayerLevelling);
}

void AHoardGameMode::InitialisePlayerHUD()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	APlayerController* PC = Cast<APlayerController>(PlayerCharacter->GetController());

	if (PC)
	{
		PC->bShowMouseCursor = false;
		PC->bEnableClickEvents = false;
		PC->bEnableMouseOverEvents = false;
	}

	if (PlayerHUDClass != nullptr)
	{
		if (CurrentWidget)
		{
			CurrentWidget->RemoveFromViewport();
		}
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);

		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void AHoardGameMode::ShowLevelUpHUD()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	APlayerController* PC = Cast<APlayerController>(PlayerCharacter->GetController());

	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
	}

	if (PlayerHUDClass != nullptr)
	{
		if (CurrentWidget)
		{
			CurrentWidget->RemoveFromViewport();
		}

		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), LevelUPHUDClass);

		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}