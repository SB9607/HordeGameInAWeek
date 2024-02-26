// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HoardGameMode.h"
#include "AICharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FIncreaseEXPAndPoints, float, Exp, float, Currency);

UCLASS()
class GAMEINAWEEK_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle WaitTimer; //Timer used so the AI will wait at after an attack

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float CurrentHealth = 20.0f; //Health of the AI

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float BaseDamage;; //Damage that the player will take

	UPROPERTY()
		AHoardGameMode* GameModeRef; //Reference to the gamemode 

	//Function that will be called when damage is applied
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;

	//Function called when the actor hits something else
	UFUNCTION()
		void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void AttackPlayer(bool isLevelling);

	void SetCanAttackToTrue();

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
		FIncreaseEXPAndPoints OnIncreaseEXPAndPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bCanAttack = true;

private:

	float Exp = 100.0f;

	float BasePoints = 100.0f;

};
