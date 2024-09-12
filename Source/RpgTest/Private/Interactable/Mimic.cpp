// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/Mimic.h"
#include "Player/PlayerZDChar.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

// AMimic: This class represents a Mimic, a character that can transform into an enemy.
AMimic::AMimic()
{
    // Enable ticking for updates
    PrimaryActorTick.bCanEverTick = true;

    // Initial Mimic status (Chest)
    Status = EMimicStatus::Chest;

    // Movement speed while in Mimic form
    MoveSpeed = 150.0f;

    // Flag indicating if the Mimic is currently chasing the player
    bIsChasingPlayer = false;
}

void AMimic::BeginPlay()
{
    Super::BeginPlay();
}

void AMimic::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Update Mimic behavior based on its current status
    if (Status == EMimicStatus::Mimic)
    {
        // Move the Mimic towards the player
        MoveMimic(DeltaTime);
    }
    else
    {
        // If not in Mimic form, stop chasing the player
        bIsChasingPlayer = false;
    }
}

void AMimic::TransformToEnemy()
{
    // Change Mimic status to Mimic
    Status = EMimicStatus::Mimic;

    // Enable collision and ticking for the Mimic
    SetActorEnableCollision(true);
    SetActorTickEnabled(true);

    // Set Mimic's attributes as an enemy
    Health = 100;
    Damage = 20;
    AttackRange = 80.0f;
    AttackCooldown = 3.f;
    MoveSpeed = 50.0f;

    // Start chasing the player
    bIsChasingPlayer = true;

    // Set the Mimic's collision profile to "Pawn" for proper interaction
    UCapsuleComponent* Capsule = FindComponentByClass<UCapsuleComponent>();
    if (Capsule)
    {
        Capsule->SetCollisionProfileName(TEXT("Pawn"));
    }

    // Log a message indicating the transformation
    UE_LOG(LogTemp, Warning, TEXT("Il mimic si è trasformato in un nemico!"));
}


void AMimic::DetermineDirection()
{
    // Determine the direction to move based on the player's position
    if (Status == EMimicStatus::Mimic)
    {
        // Get a reference to the player character
        APlayerZDChar* Player = Cast<APlayerZDChar>(UGameplayStatics::GetPlayerCharacter(this, 0));

        // Calculate the direction to the player
        if (Player)
        {
            FVector DirectionToPlayer = Player->GetActorLocation() - GetActorLocation();
            DirectionToPlayer.Z = 0; // Ignore vertical movement
            DirectionToPlayer.Normalize(); // Normalize direction vector

            // Set the direction based on dot product with cardinal directions
            if (FVector::DotProduct(DirectionToPlayer, FVector(1, 0, 0)) > 0.7f)
            {
                CurrentDirection = EMimicDirection::Right;
            }
            else if (FVector::DotProduct(DirectionToPlayer, FVector(-1, 0, 0)) > 0.7f)
            {
                CurrentDirection = EMimicDirection::Left;
            }
            else if (FVector::DotProduct(DirectionToPlayer, FVector(0, 1, 0)) > 0.7f)
            {
                CurrentDirection = EMimicDirection::Up;
            }
            else if (FVector::DotProduct(DirectionToPlayer, FVector(0, -1, 0)) > 0.7f)
            {
                CurrentDirection = EMimicDirection::Down;
            }
        }
    }
}

// Moves the Mimic towards the player and handles attacking
void AMimic::MoveMimic(float Time)
{
    if (Status == EMimicStatus::Mimic)
    {
        APlayerZDChar* Player = Cast<APlayerZDChar>(UGameplayStatics::GetPlayerCharacter(this, 0));
        if (Player)
        {
            FVector DirectionToPlayer = Player->GetActorLocation() - GetActorLocation();
            DirectionToPlayer.Z = 0; // Ignore vertical movement
            DirectionToPlayer.Normalize(); // Normalize direction vector

            DetermineDirection(); // Update current direction

            // Move the Mimic towards the player
            SetActorLocation(GetActorLocation() + DirectionToPlayer * MoveSpeed * Time);

            float DistanceToPlayer = FVector::Dist(GetActorLocation(), Player->GetActorLocation());

            // Attack if within range and cooldown permits
            if (DistanceToPlayer <= AttackRange && bCanAttack)
            {
                PerformMeleeAttack();
                StartAttackCooldown(); // Begin cooldown period after attack
            }
        }
    }
}
