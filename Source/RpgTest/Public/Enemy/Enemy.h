// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Player/PlayerZDChar.h"
#include "Enemy.generated.h"


/**
 * AEnemy class defines the behavior and properties of enemy characters in the game.
 * It inherits from the base ACharacter class provided by Unreal Engine.
 */
UCLASS()
class RPGTEST_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
    // Constructor: Sets default values for this enemy's properties
    AEnemy();

protected:

    // Called when the game starts or when the enemy is spawned in the level
    virtual void BeginPlay() override;

public:	
    // Called every frame to update the enemy's behavior, such as AI movement and attacks
    virtual void Tick(float DeltaTime) override;

    /**
     * Applies damage to the enemy.
     * This function is callable from Blueprints and reduces the enemy's health by the given damage amount.
     * @param DamageAmount The amount of damage to be applied to the enemy.
     */
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void ApplyDamage(int DamageAmount);

    // Getter function to return the current health of the enemy
    int GetHealth() {return Health;}

protected:
    /**
     * Controls the enemy's movement toward the player character.
     * Implemented with AI logic to allow the enemy to chase the player.
     */
    void MoveToPlayer();

    /**
     * Checks whether the player is within attack range.
     * If the player is within range, the enemy can attempt an attack.
     */
    void CheckAttackRange();

    /**
     * Starts the attack cooldown timer, which prevents the enemy from attacking continuously.
     * Ensures a delay between consecutive attacks.
     */
    void StartAttackCooldown();

    /**
     * Resets the attack state of the enemy, allowing the enemy to attack again after the cooldown period.
     */
    void ResetAttack();

    /**
     * Handles melee attack logic for the enemy.
     * This function is virtual, meaning it can be overridden by child classes to customize the attack behavior.
     */
    virtual void PerformMeleeAttack();

    /**
     * Handles ranged attack logic for the enemy.
     * This is also a virtual function and can be customized in derived classes.
     */
    virtual void PerformRangedAttack();

    /**
     * Applies delayed damage to the player, allowing for animations or effects to finish before applying damage.
     * Useful in cases where attack animations take time to execute.
     */
    void ApplyDamageWithDelay();

    // Components and variables

    // The PawnSensingComponent helps with AI perception, such as detecting the player’s presence.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    class UPawnSensingComponent* PawnSensingComponent;

    // Determines the distance at which the enemy can attack the player.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float AttackRange;

    // The cooldown period between consecutive attacks.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float AttackCooldown;

    // Boolean flag to indicate if the enemy is currently able to attack.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    bool bCanAttack;

    // Boolean flag to indicate if the enemy is currently chasing the player.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    bool bIsChasingPlayer;

    // Reference to the player character that the enemy is targeting.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    APlayerZDChar* TargetPlayer;

    // Boolean flag to indicate if the enemy uses ranged attacks.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    bool bIsRanged;

    // The health of the enemy. This value can be set or accessed from Blueprints.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EnemyHealth")
    int Health;
    
    // The damage amount inflicted by the enemy during attacks.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EnemyHealth")
    int Damage;

    // Timer handle for managing attack cooldown logic.
    FTimerHandle AttackCooldownTimerHandle;

    // Timer handle for applying damage with a delay.
    FTimerHandle DamageDelayTimerHandle;
};
