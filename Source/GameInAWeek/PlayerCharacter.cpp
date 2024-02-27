// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Health = 100.0f;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//Create projectile spawn location
	ProjectileSpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnLocation"));
	ProjectileSpawnLocation->SetupAttachment(RootComponent);
	ProjectileSpawnLocation->SetRelativeLocation(FVector(70.0f, 20.0f, 60.0f));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		//Shooting
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &APlayerCharacter::Shoot);

		//Interacting with objects
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerCharacter::Interact);

		//Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &APlayerCharacter::StartSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopSprint);

		//Sprinting
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Triggered, this, &APlayerCharacter::StartAim);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopAim);
	}
}


void APlayerCharacter::SetHealth(float health, bool isDamage)
{
	if (Health + health > Health)
	{
		Health = 100.0f;
	}
	else
	{
		Health += health;
	}
}

void APlayerCharacter::UpdateStamina(float valueToChange, bool isMoving)
{
	if (isMoving)
	{
		//set timer to tick down health
		if (Stamina <= 0.0f)
		{
			Stamina = 0.0f;
		}
		Stamina -= valueToChange;
	}
	else
	{
		Stamina += valueToChange;
	}

}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::Shoot(const FInputActionValue& Value)
{
	bool isShooting = Value.Get<bool>();

	if (isShooting)
	{
		//Check to see if the proijectile class is not null
		if (ProjectileClass)
		{
			
			FVector SpawnLocation = ProjectileSpawnLocation->GetComponentLocation();
			FRotator SpawnRotation = FollowCamera->GetComponentRotation();
			AProjectile* TempProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation); //Spawn a projectile at the location set

			TempProjectile->SetOwner(this); //Setting the owner of the projectile

			//Playing the gunshot sound
			//UGameplayStatics::PlaySoundAtLocation(GetWorld(), GunshotSound, GetActorLocation(), 1.0f, 1.0f, 0.0f);

			//TempProjectile->Damage *= GetGunDamage();
		}
		else
		{

			UE_LOG(LogTemp, Error, TEXT("No Projectile class set in the blueprint"));
		}
	}

}

void APlayerCharacter::Interact(const FInputActionValue& Value)
{
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//Decrease the health
	if (Health - DamageAmount <= 0)
	{
		Health = 0;
	}
	else
	{
		SetHealth(-DamageAmount, true);
	}

	//Checking to see if the player died

	return DamageAmount;
}



void APlayerCharacter::StartSprint(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	isSprinting = true;
}

void APlayerCharacter::StopSprint(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	isSprinting = false;
}

void APlayerCharacter::StartAim(const FInputActionValue& Value)
{
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void APlayerCharacter::StopAim(const FInputActionValue& Value)
{
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}
