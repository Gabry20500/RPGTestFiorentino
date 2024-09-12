// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Enemy.h"
#include "PaperFlipbookComponent.h"
#include "Mimic.generated.h"

// Enum for the direction the Mimic is facing or moving
UENUM(BlueprintType)
enum class EMimicDirection : uint8
{
    Up UMETA(DisplayName = "Up"),
    Down UMETA(DisplayName = "Down"),
    Left UMETA(DisplayName = "Left"),
    Right UMETA(DisplayName = "Right")
};

// Enum for the status of the Mimic: whether it appears as a chest or as a monster
UENUM(BlueprintType)
enum class EMimicStatus : uint8
{
    Chest UMETA(DisplayName = "Chest"),
    Mimic UMETA(DisplayName = "Mimic")
};


/**
 * AMimic class that represents a mimic enemy in the game.
 * This class inherits from AEnemy and adds additional functionality for transforming
 * between a chest and a mimic, as well as handling movement and direction.
 */
UCLASS()
class RPGTEST_API AMimic : public AEnemy
{
	GENERATED_BODY()
	
public:
    AMimic();

protected:
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime);
public:
    // Function to transform the mimic from a chest into a full-fledged enemy
    void TransformToEnemy();

private:
    // Determines the direction the mimic is facing or moving
    void DetermineDirection();

    // Handles movement of the mimic
    void MoveMimic(float Time);

    // Speed at which the mimic moves
    float MoveSpeed;

    // Current direction of the mimic
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mimic", meta = (AllowPrivateAccess = "true"))
    EMimicDirection CurrentDirection;

    // Current status of the mimic (chest or active enemy)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mimic", meta = (AllowPrivateAccess = "true"))
    EMimicStatus Status;
};
