// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HoardGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRespawnEnemies);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FIncreasePlayerEXPAndPoints, float, Exp, float, Points);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerLevelling, bool, IsLevelling);

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> PlayerHUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> LevelUPHUDClass;

	UPROPERTY()
	class UUserWidget* CurrentWidget;

	UPROPERTY()
		int remainingEnemies;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
		FRespawnEnemies OnRespawnEnemies;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
		FIncreasePlayerEXPAndPoints OnIncreasePlayerEXPAndPoints;

		UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
		FPlayerLevelling OnIsLevelling;

	void CheckRemainingEnemies();

	void IncreasePlayerEXPAndPoints(float EXP, float Points);

	UFUNCTION(BlueprintCallable)
	void IsPlayerLevelling(bool isPlayerLevelling);

	UFUNCTION(BlueprintCallable)
	void InitialisePlayerHUD();

	UFUNCTION(BlueprintCallable)
	void ShowLevelUpHUD();

	UPROPERTY()
		bool bIsLevelling = false;

	UPROPERTY(BlueprintReadOnly)
		int roundNumber = 0;

private:

	
};
