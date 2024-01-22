// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind the functions to the input axis
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
}

void APlayerCharacter::MoveForward(float Value)
{
	// Get the forward vector
	FVector ForwardVector = GetActorRightVector();

	// Update the character's location based on input
	AddMovementInput(ForwardVector, Value);
}

void APlayerCharacter::MoveRight(float Value)
{
	// Get the right vector
	FVector RightVector = GetActorForwardVector();

	// Update the character's location based on input
	AddMovementInput(RightVector, Value);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}
