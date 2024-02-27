// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEINAWEEK_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:

	FTimerHandle WaitTimer; //Timer used so the AI will wait at each waypoint it goes to

protected:
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:

	UPROPERTY(EditAnywhere)
		float WaitDuration = 3.0f; //The wait amount that the AI will wait at a checkpoint

	APawn* PlayerCharRef; //Referece to the player pawn

	bool canEnemyAttack;

};
