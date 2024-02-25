// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class GAMEINAWEEK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float MovementSpeed = 3000.0f; //Setting the movespeed of the projectile

	UPROPERTY(EditAnywhere)
	float Damage = 10.0f; //Setting the base damage of each projectile

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh; //Mesh to be set in editor

	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* ProjectileMovement; //Reference to the projectile movement component

private:
	//Function called when the actor hits something else
	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
};
