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
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::Attack);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &APlayerCharacter::StopAttack);
	PlayerInputComponent->BindAction("Defend", IE_Pressed, this, &APlayerCharacter::Defend);
	PlayerInputComponent->BindAction("Defend", IE_Released, this, &APlayerCharacter::StopDefend);
}

void APlayerCharacter::MoveForward(float Value)
{
	// Get the forward vector
	FVector ForwardVector = GetActorRightVector();

	// Update the character's location based on input
	AddMovementInput(ForwardVector, Value);

	if(Value < 0)
	{
		Direction = 1;
	}else if(Value > 0)
	{
		Direction = 0;
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	// Get the right vector
	FVector RightVector = GetActorForwardVector();

	// Update the character's location based on input
	AddMovementInput(RightVector, Value);

	if(Value < 0)
	{
		Direction = 2;
	}else if(Value > 0)
	{
		Direction = 3;
	}
}

void APlayerCharacter::Attack()
{
	IsAttacking = true;
	GetLocalViewingPlayerController()->SetIgnoreMoveInput(true);
	GetLocalViewingPlayerController()->SetIgnoreLookInput(true);
}

void APlayerCharacter::StopAttack()
{
	IsAttacking = false;
	GetLocalViewingPlayerController()->SetIgnoreMoveInput(false);
	GetLocalViewingPlayerController()->SetIgnoreLookInput(false);
}

void APlayerCharacter::Defend()
{
	IsDefending = true;
	GetLocalViewingPlayerController()->SetIgnoreMoveInput(true);
	GetLocalViewingPlayerController()->SetIgnoreLookInput(true);
}

void APlayerCharacter::StopDefend()
{
	IsDefending = false;
	GetLocalViewingPlayerController()->SetIgnoreMoveInput(false);
	GetLocalViewingPlayerController()->SetIgnoreLookInput(false);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}
