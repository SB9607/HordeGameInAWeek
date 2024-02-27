// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AICharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setting up the mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetSimulatePhysics(true);
	Mesh->SetNotifyRigidBodyCollision(true);
	SetRootComponent(Mesh);

	//Setting up the projectile movement component
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->MaxSpeed = MovementSpeed;
	ProjectileMovement->InitialSpeed = MovementSpeed;
	InitialLifeSpan = 4.0f; //Setting the lifespan so after a set amount of time they will despawn

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	//Adding a delegate that will handle the on hit functionality
	OnActorHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{

	AActor* ProjectileOwner = GetOwner(); //Getting the owner of the projectile
	//Making sure the owner is not null
	if (ProjectileOwner == nullptr || ProjectileOwner == NULL)
	{
		return;
	}
	else
	{
		//Making sure the other actor that is hit is not null
		if (OtherActor != nullptr || OtherActor != NULL)
		{
			//Checking if the actor hit is the explosive crate
			if (OtherActor->GetClass()->IsChildOf(AAICharacter::StaticClass()))
			{

				//Applying damage to the crate when it is hit
				UGameplayStatics::ApplyDamage(
					OtherActor, //actor that will be damaged
					Damage, //the base damage to apply
					ProjectileOwner->GetInstigatorController(), //controller that caused the damage
					this, //Actor that actually caused the damage
					UDamageType::StaticClass() //class that describes the damage that was done
				);
				//Destroy the projectile when it hits
				Destroy();
			}
		}
	}

}
