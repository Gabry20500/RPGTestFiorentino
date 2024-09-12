// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/SlimeEnemy.h"

// Constructor: Initializes default values specific to the Slime enemy
ASlimeEnemy::ASlimeEnemy()
{
    Health = 80;               // Sets the slime's health to 80
    Damage = 15;               // Sets the damage dealt by the slime to 15
    AttackRange = 100.0f;      // Sets the attack range for melee combat (slime is not a ranged attacker)
    AttackCooldown = 2.0f;     // Sets the cooldown period between attacks to 2 seconds
    bIsRanged = false;         // Specifies that this enemy is not a ranged attacker

    PoisonDamage = 5.f;        // Sets the additional poison damage dealt by the slime to 5
}

// Called when the game starts or when the slime enemy is spawned
void ASlimeEnemy::BeginPlay()
{
    Super::BeginPlay(); // Calls the base class BeginPlay() to initialize inherited properties and behaviors
}

// Performs a melee attack and applies additional poison damage to the player
void ASlimeEnemy::PerformMeleeAttack()
{
    UE_LOG(LogTemp, Warning, TEXT("Slime attacks with melee!")); // Logs a message indicating a melee attack

    Super::PerformMeleeAttack(); // Calls the base class implementation to handle the default melee attack logic

    // Checks if there is a valid target player
    if (TargetPlayer)
    {
        // Applies a poisoned state to the player with additional poison damage
        TargetPlayer->ApplyState(EPlayerState::Poisoned, PoisonDamage);
    }
}
