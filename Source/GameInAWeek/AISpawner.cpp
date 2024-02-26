// Fill out your copyright notice in the Description page of Project Settings.


#include "AISpawner.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AAISpawner::AAISpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAISpawner::BeginPlay()
{
	Super::BeginPlay();
	
	NumberOfEnemies = 2;
	SpawnIncrement = 1;

	GameModeRef = Cast<AHoardGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	GameModeRef->OnRespawnEnemies.AddDynamic(this, &AAISpawner::SpawnEnemies);
}

// Called every frame
void AAISpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAISpawner::SpawnEnemies()
{
	if (Enemy != NULL || Enemy != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning enemies"));
		for (int i = 1; i < NumberOfEnemies; i++)
		{
			FActorSpawnParameters SpawnParameters;

			SpawnParameters.bNoFail = true;

			auto* tempEnemy = GetWorld()->SpawnActor<AAICharacter>(Enemy, { this->GetActorLocation().X + FMath::RandRange(i * -100,i * 100),GetActorLocation().Y + FMath::RandRange(i * -100,i * 100),this->GetActorLocation().Z }, { 0,0,0 }, SpawnParameters);

			tempEnemy->SetActorEnableCollision(false);

			if (tempEnemy)
			{
				tempEnemy->CurrentHealth = EnemyHealth;
				tempEnemy->BaseDamage = 10.0f;

				tempEnemy->SetActorEnableCollision(true);

				tempEnemy = nullptr;
			}
		}
	}

	SpawnIncrement++;
	EnemyHealth += 10.0f;
	NumberOfEnemies += SpawnIncrement;
}