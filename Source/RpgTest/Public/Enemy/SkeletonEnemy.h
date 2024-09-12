// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Enemy.h"
#include "Projectile/Projectile.h"
#include "SkeletonEnemy.generated.h"

// Enum to define possible movement directions for the skeleton enemy
UENUM(BlueprintType)
enum class ESkeletonDirection : uint8
{
	Up UMETA(DisplayName = "Up"),       // Skeleton moving upward
	Down UMETA(DisplayName = "Down"),   // Skeleton moving downward
	Left UMETA(DisplayName = "Left"),   // Skeleton moving left
	Right UMETA(DisplayName = "Right")  // Skeleton moving right
};

/**
 * SkeletonEnemy class - a ranged enemy that fires projectiles.
 */
UCLASS()
class RPGTEST_API ASkeletonEnemy : public AEnemy
{
	GENERATED_BODY()
	
public:
	// Constructor: Initializes default properties for SkeletonEnemy
	ASkeletonEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Override for ranged attack functionality specific to SkeletonEnemy
	virtual void PerformRangedAttack() override;

	// Tracks the current direction the skeleton is facing/moving
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skeleton", meta = (AllowPrivateAccess = "true"))
	ESkeletonDirection CurrentDirection;

	// Determines the skeleton's movement direction based on the player's position
	void DetermineDirection();

	// Class reference for the projectile the skeleton will fire
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;
};
