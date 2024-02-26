// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HoardGameMode.h"
#include "AICharacter.h"
#include "AISpawner.generated.h"

UCLASS()
class GAMEINAWEEK_API AAISpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAISpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
		TSubclassOf<AAICharacter> Enemy;

private:

	UPROPERTY()
		AHoardGameMode* GameModeRef; //Reference to the gamemode 

	int NumberOfEnemies;

	int SpawnIncrement;

	float EnemyHealth = 20.0f;

	UFUNCTION()
		void SpawnEnemies();
};
