// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HoardGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRespawnEnemies);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FIncreasePlayerEXPAndPoints, float, Exp, float, Points);

/**
 * 
 */
UCLASS()
class GAMEINAWEEK_API AHoardGameMode : public AGameModeBase
{
	GENERATED_BODY()
	

protected:

	virtual void BeginPlay() override;

public:

	UPROPERTY()
		int remainingEnemies;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
		FRespawnEnemies OnRespawnEnemies;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
		FIncreasePlayerEXPAndPoints OnIncreasePlayerEXPAndPoints;

	void CheckRemainingEnemies();

	void IncreasePlayerEXPAndPoints(float EXP, float Points);

	UPROPERTY()
		bool bIsLevelling = false;

private:

	UPROPERTY()
		int roundNumber = 0;
};
