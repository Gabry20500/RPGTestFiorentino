// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Enemy.h"
#include "Projectile/Projectile.h"
#include "GhostEnemy.generated.h"


/**
 * Enum to define possible movement directions for the GhostEnemy.
 * The enum values can be used in Blueprints to specify the direction.
 */
UENUM(BlueprintType)
enum class EGhostDirection : uint8
{
    Up UMETA(DisplayName = "Up"),
    Down UMETA(DisplayName = "Down"),
    Left UMETA(DisplayName = "Left"),
    Right UMETA(DisplayName = "Right")
};


/**
 * AGhostEnemy class represents a specialized enemy that extends from AEnemy.
 * It features additional mechanics like projectile attacks and directional movement.
 */
UCLASS()
class RPGTEST_API AGhostEnemy : public AEnemy
{
	GENERATED_BODY()
	
public:
    // Constructor to initialize default values for the GhostEnemy
    AGhostEnemy();

protected:
    // Called when the game starts or when the enemy is spawned
    virtual void BeginPlay() override;

    // Called every frame to update GhostEnemy behavior
    virtual void Tick(float DeltaTime) override;

    /**
    * Override of the base class's ranged attack function.
    * The GhostEnemy shoots projectiles instead of a default attack.
    */    
    virtual void PerformRangedAttack() override;

    // The current movement direction of the GhostEnemy, can be changed dynamically
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skeleton", meta = (AllowPrivateAccess = "true"))
    EGhostDirection CurrentDirection;

    /**
     * Logic to determine the GhostEnemy's movement direction based on gameplay conditions.
     * This function can be expanded to change direction dynamically during gameplay.
     */
    void DetermineDirection();

    // The projectile class that the GhostEnemy will spawn during a ranged attack
    UPROPERTY(EditAnywhere, Category = "Combat")
    TSubclassOf<class AProjectile> ProjectileClass;
};
