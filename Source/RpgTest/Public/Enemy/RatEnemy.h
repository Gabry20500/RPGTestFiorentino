// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Enemy.h"
#include "RatEnemy.generated.h"


/**
 * Enum to define possible movement directions for the RatEnemy.
 * The enum values can be used in Blueprints to specify the direction.
 */
UENUM(BlueprintType)
enum class ERatDirection : uint8
{
    Up UMETA(DisplayName = "Up"),
    Down UMETA(DisplayName = "Down"),
    Left UMETA(DisplayName = "Left"),
    Right UMETA(DisplayName = "Right")
};

/**
 * ARatEnemy class represents a specialized melee enemy derived from AEnemy.
 * The class features directional movement and additional mechanics like burn damage.
 */
UCLASS()
class RPGTEST_API ARatEnemy : public AEnemy
{
	GENERATED_BODY()
public:
    // Constructor: Initializes default values for the RatEnemy
    ARatEnemy();

protected:
    // Called when the game starts or when the enemy is spawned
    virtual void BeginPlay() override;

    // Override for the melee attack behavior of the RatEnemy
    virtual void PerformMeleeAttack() override;

    // Called every frame to update RatEnemy's behavior
    virtual void Tick(float DeltaTime) override;

private:
    // Holds the current direction the RatEnemy is facing or moving towards
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rat", meta = (AllowPrivateAccess = "true"))
    ERatDirection CurrentDirection;

    // The burn damage applied by the RatEnemy's attacks (e.g., poison or fire)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Poison", meta = (AllowPrivateAccess = "true"))
    float BurnDamage;

    /**
     * Logic to determine the RatEnemy's movement direction relative to the player's position.
     * This can be used for animations or attack adjustments.
     */
    void DetermineDirection();
 
};
