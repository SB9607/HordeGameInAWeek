// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuGameMode.h"
#include "Kismet/GameplayStatics.h"

void AMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	//Showing the cursor when on menus
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
}