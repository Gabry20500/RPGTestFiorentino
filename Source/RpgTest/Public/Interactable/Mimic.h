// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Enemy.h"
#include "PaperFlipbookComponent.h"
#include "Mimic.generated.h"

UENUM(BlueprintType)
enum class EMimicDirection : uint8
{
    Up,
    Down,
    Left,
    Right
};

UENUM(BlueprintType)
enum class EMimicStatus : uint8
{
    Chest,
    Mimic
};



/**
 * 
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
    // Funzione per trasformare il mimic in un nemico
    void TransformToEnemy();

private:
    void DetermineDirection();

    void MoveMimic(float Time);

    float MoveSpeed;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mimic", meta = (AllowPrivateAccess = "true"))
    EMimicDirection CurrentDirection;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mimic", meta = (AllowPrivateAccess = "true"))
    EMimicStatus Status;
};
