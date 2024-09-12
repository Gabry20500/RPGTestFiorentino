// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Enemy.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values for the enemy
AEnemy::AEnemy()
{
    // Enable ticking to call Tick() every frame for real-time behavior updates
    PrimaryActorTick.bCanEverTick = true;

    // Initialize basic enemy stats and properties
    Health = 100;
    Damage = 20;
    AttackRange = 100.0f; // Range within which the enemy can attack
    AttackCooldown = 2.0f; // Time between consecutive attacks
    bIsRanged = false; // Default to melee attacks; can be changed to ranged
    bIsChasingPlayer = false; // Initially not chasing the player
    bCanAttack = true; // The enemy starts off able to attack
}

// Called when the game starts or when the enemy is spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

    // If the enemy doesn't have a controller (AI), assign a default controller
    if (!GetController())
    {
        SpawnDefaultController();
    }

    // Get a reference to the player character
    APlayerZDChar* PlayerCharacter = Cast<APlayerZDChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    if (PlayerCharacter)
    {
        TargetPlayer = PlayerCharacter; // Set the player as the target
        if (TargetPlayer)
        {
            bIsChasingPlayer = true; // Start chasing the player
        }
    }
}

// Called every frame to update enemy behavior
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // If the enemy is chasing the player, move toward them and check attack range
    if (bIsChasingPlayer)
    {
        MoveToPlayer();
        CheckAttackRange();
    }
}

// Apply damage to the enemy, reducing health
void AEnemy::ApplyDamage(int DamageAmount)
{
    Health -= DamageAmount; // Subtract the damage amount from the enemy's health

    // Check if the enemy's health has reached zero or below
    if (Health <= 0)
    {
        Health = 0; // Clamp the health at zero

        // Award experience points to the player for killing the enemy
        if (TargetPlayer)
        {
            int32 XPReward = 20; // Set the experience points reward
            TargetPlayer->GainXP(XPReward); // Player gains XP
        }

        Destroy(); // Destroy the enemy actor upon death
    }

    // Log the current health for debugging purposes
    UE_LOG(LogTemp, Log, TEXT("%d"), Health);
}

// Move the enemy toward the player using the AIController
void AEnemy::MoveToPlayer()
{
    if (TargetPlayer)
    {
        AAIController* AIController = Cast<AAIController>(GetController());
        if (AIController)
        {
            AIController->MoveToActor(TargetPlayer); // Command the AI to move toward the player
        }
    }
}

// Check if the player is within attack range and perform an attack if possible
void AEnemy::CheckAttackRange()
{
    if (TargetPlayer && bCanAttack)
    {
        // Calculate the distance between the enemy and the player
        float DistanceToPlayer = FVector::Dist(GetActorLocation(), TargetPlayer->GetActorLocation());

        // If the player is within attack range
        if (DistanceToPlayer <= AttackRange)
        {
            // Perform either a ranged or melee attack depending on enemy type
            if (bIsRanged)
            {
                PerformRangedAttack();
            }
            else
            {
                PerformMeleeAttack();
            }

            // Start the attack cooldown to prevent continuous attacks
            StartAttackCooldown();
        }
    }
}

// Begin the cooldown period after an attack
void AEnemy::StartAttackCooldown()
{
    bCanAttack = false; // Disable attacks during cooldown

    // Set a timer to reset the attack state after the cooldown duration
    GetWorldTimerManager().SetTimer(
        AttackCooldownTimerHandle,
        this,
        &AEnemy::ResetAttack,
        AttackCooldown,
        false
    );
}

// Reset the attack state, allowing the enemy to attack again
void AEnemy::ResetAttack()
{
    bCanAttack = true; // Re-enable attacks after cooldown
}

// Perform a melee attack on the player
void AEnemy::PerformMeleeAttack()
{
    UE_LOG(LogTemp, Warning, TEXT("Base Melee Attack!"));
    if (TargetPlayer)
    {
        // Apply damage directly to the player
        TargetPlayer->ApplyDamage(Damage);
    }

    // Ensure that the attack respects the cooldown
    StartAttackCooldown();
}

// Perform a ranged attack on the player
void AEnemy::PerformRangedAttack()
{
    if (TargetPlayer)
    {
        UE_LOG(LogTemp, Warning, TEXT("Ranged Attack!"));

        // Set a delay before applying damage to simulate projectile travel time
        GetWorldTimerManager().SetTimer(
            DamageDelayTimerHandle,
            this,
            &AEnemy::ApplyDamageWithDelay,
            2.0f, // 2-second delay before damage is applied
            false
        );
    }
}

// Apply damage to the player after a delay (used for ranged attacks)
void AEnemy::ApplyDamageWithDelay()
{
    if (TargetPlayer) 
    {
        // Apply damage to the player after the delay
        TargetPlayer->ApplyDamage(Damage);
    }
}

