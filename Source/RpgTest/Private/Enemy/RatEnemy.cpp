// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/RatEnemy.h"
#include "Kismet/GameplayStatics.h"

// Constructor: Initializes default values for the RatEnemy
ARatEnemy::ARatEnemy()
{
    // Set RatEnemy specific stats
    Health = 50;                  // Lower health compared to other enemies
    Damage = 10;                   // Melee attack damage
    AttackRange = 100.0f;          // Short range for melee attacks
    AttackCooldown = 1.5f;         // Shorter cooldown for fast attacks
    bIsRanged = false;             // RatEnemy uses melee attacks

    BurnDamage = 5.0f;             // Additional burn damage over time applied to the player
}

// Called when the game starts or the enemy is spawned
void ARatEnemy::BeginPlay()
{
    Super::BeginPlay(); // Ensure the base class BeginPlay() is called
}

// Overriding the melee attack logic for the RatEnemy
void ARatEnemy::PerformMeleeAttack()
{    
    // Call base melee attack functionality
    Super::PerformMeleeAttack();

    // Apply burn damage to the target player if they exist
    if (TargetPlayer)
    {
        // Apply a burning state to the player with the specified burn damage
        TargetPlayer->ApplyState(EPlayerState::Burning, BurnDamage);
    }
}

// Called every frame to update the RatEnemy's behavior
void ARatEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // If chasing the player, move towards them, check attack range, and determine direction
    if (bIsChasingPlayer)
    {
        MoveToPlayer();       // Move towards the player's position
        CheckAttackRange();   // Check if the player is within attack range
        DetermineDirection(); // Update the current movement direction
    }
}

// Determines the RatEnemy's movement direction relative to the player's position
void ARatEnemy::DetermineDirection()
{
    // Ensure the TargetPlayer exists before determining direction
    if (TargetPlayer)
    {
        // Calculate the vector pointing from the RatEnemy to the player, ignoring the Z-axis (height)
        FVector DirectionToPlayer = TargetPlayer->GetActorLocation() - GetActorLocation();
        DirectionToPlayer.Z = 0; // Ignore vertical differences

        DirectionToPlayer.Normalize(); // Normalize the vector to get only direction

        // Compare the normalized direction vector to cardinal directions (Up, Down, Left, Right)
        if (FVector::DotProduct(DirectionToPlayer, FVector(1, 0, 0)) > 0.7f)
        {
            CurrentDirection = ERatDirection::Up; // Enemy is facing upwards
        }
        else if (FVector::DotProduct(DirectionToPlayer, FVector(-1, 0, 0)) > 0.7f)
        {
            CurrentDirection = ERatDirection::Down; // Enemy is facing downwards
        }
        else if (FVector::DotProduct(DirectionToPlayer, FVector(0, 1, 0)) > 0.7f)
        {
            CurrentDirection = ERatDirection::Right; // Enemy is facing right
        }
        else if (FVector::DotProduct(DirectionToPlayer, FVector(0, -1, 0)) > 0.7f)
        {
            CurrentDirection = ERatDirection::Left; // Enemy is facing left
        }
    }
}
