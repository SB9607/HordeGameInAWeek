// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "HoardGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.generated.h"

class USceneComponent;
class AProjectile;

UCLASS()
class GAMEINAWEEK_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Shoot Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ShootAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

	/** Sprint Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SprintAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AimAction;



public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle ShootTimer; //Timer used so the AI will wait at after an attack

	FTimerHandle TimeTillExtractTimer;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for shooting input */
	void Shoot(const FInputActionValue& Value);

	void SpawnAndFireProjectile();

	/** Called for interacting with objects */
	void Interact(const FInputActionValue& Value);

	/** Called for sprinting */
	void StartSprint(const FInputActionValue& Value);
	void StopSprint(const FInputActionValue& Value);

	/** Called for Aiming */
	void StartAim(const FInputActionValue& Value);
	void StopAim(const FInputActionValue& Value);


	UPROPERTY(EditAnywhere, Category = "UI")
	float BaseHealth;

	UPROPERTY(EditAnywhere, Category = "UI")
	float NeededEXP = 100.0f;

	UPROPERTY(EditAnywhere, Category = "UI")
	float CurrentEXP = 0.0f;

	UPROPERTY(EditAnywhere, Category = "UI")
	int CurrentLevel = 1;

	UPROPERTY(EditAnywhere, Category = "UI")
	float CurrentStamina = 100.0f;

	UPROPERTY(EditAnywhere, Category = "UI")
	float Currency = 0.0f;

	UPROPERTY(EditAnywhere, Category = "UI")
	float GunDamage = 1.0f;

	UPROPERTY(EditAnywhere, Category = "UI")
	float FireRate = 3.0f;

	float TimeRemaining;

	UPROPERTY()
	FString Information = "";

	UPROPERTY()
	AHoardGameMode* GameModeRef; //Reference to the gamemode 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(EditAnywhere)
	USceneComponent* ProjectileSpawnLocation; //Location to spawn the projectile when shot

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> ProjectileClass; //Projectile that is shot when the player shoots the gun

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
	float Stamina = 100.0f;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	float WalkSpeed = 500.0f;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	float SprintSpeed = 1000.0f;

	bool isSprinting = false;

	void SetHealth(float health, bool isDamage);

	void UpdateStamina(float valueToChange, bool isMoving);

	UFUNCTION(BlueprintCallable)
	float GetBaseHealth();

	UFUNCTION(BlueprintCallable)
	void IncreaseBaseHealth(float healthToIncreaseBy);

	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth();

	UFUNCTION(BlueprintCallable)
	float GetNeededEXP();

	UFUNCTION(BlueprintCallable)
	void SetNeededEXP(float NeededEXPToLevel);

	UFUNCTION(BlueprintCallable)
	float GetCurrentEXP();

	UFUNCTION(BlueprintCallable)
	void SetCurrentEXP(float GainedEXP);

	UFUNCTION(BlueprintCallable)
	int GetCurrentLevel();

	UFUNCTION(BlueprintCallable)
	void SetCurrentLevel(int Level);

	UFUNCTION(BlueprintCallable)
	float GetCurrentCurrency();

	UFUNCTION(BlueprintCallable)
	void SetCurrentCurrency(float Points);

	UFUNCTION(BlueprintCallable)
	float GetGunDamage();

	UFUNCTION(BlueprintCallable)
	void SetGunDamage(float DamageToIncreaseBy);

	UFUNCTION(BlueprintCallable)
	float GetFireRate();

	UFUNCTION(BlueprintCallable)
	void SetFireRate(float AmountToDecreaseBy);

	UFUNCTION(BlueprintCallable)
	void SetInfo(FString info);

	UFUNCTION()
	void IncreaseEXPAndPoints(float Exp, float Points);

	UFUNCTION()
	void LevelUp();

	UFUNCTION()
	void ClearInfoText();

	UFUNCTION(BlueprintCallable)
	FString DisplayInfo();

	void UpdateTimeRemaining();

	UFUNCTION(BlueprintCallable)
	float GetTimeRemaining();

	UFUNCTION()
	//Function that will be called when damage is applied
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;

};
