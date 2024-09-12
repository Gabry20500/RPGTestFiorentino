// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/GhostEnemy.h"

// Constructor: Initializes GhostEnemy properties
AGhostEnemy::AGhostEnemy()
{
    // Set specific stats for GhostEnemy
    Health = 60;                  // Lower health compared to standard enemies
    Damage = 10;                   // Damage dealt by ranged attacks
    AttackRange = 2000.0f;         // Longer range for projectile-based attacks
    AttackCooldown = 2.5f;         // Cooldown between attacks
    bIsRanged = true;              // GhostEnemy uses ranged attacks
}

// Called when the game starts or the enemy is spawned
void AGhostEnemy::BeginPlay()
{
    Super::BeginPlay(); // Ensure the base class BeginPlay() is called
}

// Called every frame to update the GhostEnemy's behavior
void AGhostEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // If chasing the player, move towards them, check attack range, and update direction
    if (bIsChasingPlayer)
    {
        MoveToPlayer();      // Move towards the player
        CheckAttackRange();  // Check if within range to attack
        DetermineDirection(); // Determine the direction relative to the player
    }
}

// Override of the ranged attack function for the GhostEnemy
void AGhostEnemy::PerformRangedAttack()
{
    // Ensure that there is a target and a projectile class is set
    if (TargetPlayer && ProjectileClass)
    {
        // Calculate the spawn location for the projectile (above the enemy's base location)
        FVector MuzzleLocation = GetActorLocation() + FVector(0, 0, 50); // Offset upwards
        // Calculate the rotation needed to aim towards the player
        FRotator MuzzleRotation = (TargetPlayer->GetActorLocation() - MuzzleLocation).Rotation();

        UWorld* World = GetWorld();
        if (World)
        {
            // Spawn the projectile at the calculated location and rotation
            AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation);
            if (Projectile)
            {
                // Set the damage for the projectile
                Projectile->SetDamage(Damage);

                // Determine the direction the projectile should be launched
                FVector LaunchDirection = MuzzleRotation.Vector();
                Projectile->SetVelocity(LaunchDirection); // Set the velocity for the projectile
            }
        }
    }
}

// Determines the direction of the GhostEnemy relative to the player's position
void AGhostEnemy::DetermineDirection()
{
    if (TargetPlayer)
    {
        // Calculate the vector pointing from the enemy to the player, ignoring the Z axis (height)
        FVector DirectionToPlayer = TargetPlayer->GetActorLocation() - GetActorLocation();
        DirectionToPlayer.Z = 0; // Ignore vertical direction

        DirectionToPlayer.Normalize(); // Normalize to get only direction

        // Compare direction vector to cardinal directions (Up, Down, Left, Right)
        if (FVector::DotProduct(DirectionToPlayer, FVector(1, 0, 0)) > 0.7f)
        {
            CurrentDirection = EGhostDirection::Up; // Facing upwards
        }
        else if (FVector::DotProduct(DirectionToPlayer, FVector(-1, 0, 0)) > 0.7f)
        {
            CurrentDirection = EGhostDirection::Down; // Facing downwards
        }
        else if (FVector::DotProduct(DirectionToPlayer, FVector(0, 1, 0)) > 0.7f)
        {
            CurrentDirection = EGhostDirection::Right; // Facing right
        }
        else if (FVector::DotProduct(DirectionToPlayer, FVector(0, -1, 0)) > 0.7f)
        {
            CurrentDirection = EGhostDirection::Left; // Facing left
        }
    }
}
