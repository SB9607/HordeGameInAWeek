// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//Adding a delegate that will handle the on hit functionality
	OnActorHit.AddDynamic(this, &AAICharacter::OnHit);

	GameModeRef = Cast<AHoardGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	GameModeRef->remainingEnemies++;
	GameModeRef->CheckRemainingEnemies();
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


float AAICharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	CurrentHealth -= DamageAmount; //Decrease the health

	//Checking to see if the AI died
	if (CurrentHealth <= 0.0f)
	{
		GameModeRef->remainingEnemies--;
		GameModeRef->CheckRemainingEnemies();
		Destroy();

		GameModeRef->IncreasePlayerEXPAndPoints(Exp, BasePoints);

	}
	return DamageAmount;
}

void AAICharacter::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	//Making sure the owner is not null
	if (SelfActor == nullptr || SelfActor == NULL)
	{
		return;
	}
	else
	{
		//Making sure the other actor that is hit is not null
		if (OtherActor != nullptr || OtherActor != NULL)
		{
			if (bCanAttack)
			{
				//Checking if the actor hit is the explosive crate
				if (OtherActor->GetClass()->IsChildOf(APlayerCharacter::StaticClass()))
				{
					bCanAttack = false;

					//Applying damage to the crate when it is hit
					UGameplayStatics::ApplyDamage(
						OtherActor, //actor that will be damaged
						BaseDamage, //the base damage to apply
						GetController(), //controller that caused the damage
						this, //Actor that actually caused the damage
						UDamageType::StaticClass() //class that describes the damage that was done
					);

					GetWorld()->GetTimerManager().SetTimer(WaitTimer, this, &AAICharacter::SetCanAttackToTrue, 2.0f, false);
				}
			}
		}
	}
}

void AAICharacter::AttackPlayer(bool isLevelling)
{
	if (isLevelling)
	{
		bCanAttack = false;
	}
	else
	{
		bCanAttack = true;
	}
}

void AAICharacter::SetCanAttackToTrue()
{
	bCanAttack = true;
	GetWorld()->GetTimerManager().ClearTimer(WaitTimer);
}
