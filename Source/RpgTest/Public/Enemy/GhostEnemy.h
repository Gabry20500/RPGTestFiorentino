// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Enemy.h"
#include "Projectile/Projectile.h"
#include "GhostEnemy.generated.h"


UENUM(BlueprintType)
enum class EGhostDirection : uint8
{
    Up UMETA(DisplayName = "Up"),
    Down UMETA(DisplayName = "Down"),
    Left UMETA(DisplayName = "Left"),
    Right UMETA(DisplayName = "Right")
};


/**
 * 
 */
UCLASS()
class RPGTEST_API AGhostEnemy : public AEnemy
{
	GENERATED_BODY()
	
public:
    AGhostEnemy();

protected:
    virtual void BeginPlay() override;

    // Override dell'attacco ranged
    virtual void PerformRangedAttack() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skeleton", meta = (AllowPrivateAccess = "true"))
    EGhostDirection CurrentDirection;

    void DetermineDirection();

    // Classe del proiettile da spawnare
    UPROPERTY(EditAnywhere, Category = "Combat")
    TSubclassOf<class AProjectile> ProjectileClass;
};
