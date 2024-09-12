// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/SkeletonEnemy.h"

// Constructor: Initializes default values for the skeleton enemy
ASkeletonEnemy::ASkeletonEnemy()
{
    Health = 80;              // Skeleton's health is set to 80
    Damage = 15;              // Skeleton deals 15 damage with each attack
    AttackRange = 900.0f;     // Skeleton can attack from 900 units away (ranged combat)
    AttackCooldown = 3.0f;    // Cooldown time between attacks is set to 3 seconds
    bIsRanged = true;         // This enemy uses ranged attacks (skeleton is a ranged combatant)
}

// Called when the game starts or when spawned
void ASkeletonEnemy::BeginPlay()
{
    Super::BeginPlay(); // Calls the base class BeginPlay() for any additional setup
}

// Called every frame
void ASkeletonEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime); // Call to base class Tick() to handle any inherited behavior

    // Check if the skeleton is chasing the player
    if (bIsChasingPlayer)
    {
        MoveToPlayer();         // Move towards the player's current location
        CheckAttackRange();     // Check if the player is within attack range
        DetermineDirection();   // Determine the direction the skeleton is facing relative to the player
    }
}

// Executes a ranged attack using a projectile when the player is within range
void ASkeletonEnemy::PerformRangedAttack()
{
    // Ensure there is a valid player to target and a valid projectile class
    if (TargetPlayer && ProjectileClass)
    {
        // Calculate the position from where the projectile will be fired (slightly above the skeleton)
        FVector MuzzleLocation = GetActorLocation() + FVector(0, 0, 50);

        // Determine the rotation needed to aim at the player's location
        FRotator MuzzleRotation = (TargetPlayer->GetActorLocation() - MuzzleLocation).Rotation();

        UWorld* World = GetWorld(); // Get a reference to the game world
        if (World)
        {
            // Spawn a projectile using the predefined ProjectileClass
            AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation);
            if (Projectile)
            {
                // Set the projectile's damage based on the skeleton's damage property
                Projectile->SetDamage(Damage);

                // Calculate the direction in which to launch the projectile
                FVector LaunchDirection = MuzzleRotation.Vector();

                // Set the projectile's velocity in the calculated direction
                Projectile->SetVelocity(LaunchDirection);
            }
        }
    }
}

// Determines the skeleton's movement direction relative to the player's position
void ASkeletonEnemy::DetermineDirection()
{
    if (TargetPlayer)
    {
        // Calculate the vector from the skeleton to the player, ignoring vertical difference (Z-axis)
        FVector DirectionToPlayer = TargetPlayer->GetActorLocation() - GetActorLocation();
        DirectionToPlayer.Z = 0; // Ensure movement direction is limited to the XY plane

        DirectionToPlayer.Normalize(); // Normalize the direction vector for accurate comparison

        // Set the skeleton's current direction based on the normalized direction vector
        if (FVector::DotProduct(DirectionToPlayer, FVector(1, 0, 0)) > 0.7f)
        {
            CurrentDirection = ESkeletonDirection::Up;
        }
        else if (FVector::DotProduct(DirectionToPlayer, FVector(-1, 0, 0)) > 0.7f)
        {
            CurrentDirection = ESkeletonDirection::Down;
        }
        else if (FVector::DotProduct(DirectionToPlayer, FVector(0, 1, 0)) > 0.7f)
        {
            CurrentDirection = ESkeletonDirection::Right;
        }
        else if (FVector::DotProduct(DirectionToPlayer, FVector(0, -1, 0)) > 0.7f)
        {
            CurrentDirection = ESkeletonDirection::Left;
        }
    }
}
