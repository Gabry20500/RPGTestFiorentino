// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Enemy.h"
#include "RatEnemy.generated.h"


UENUM(BlueprintType)
enum class ERatDirection : uint8
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
class RPGTEST_API ARatEnemy : public AEnemy
{
	GENERATED_BODY()
public:
    ARatEnemy();

protected:
    virtual void BeginPlay() override;

    virtual void PerformMeleeAttack() override;

    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rat", meta = (AllowPrivateAccess = "true"))
    ERatDirection CurrentDirection;

    void DetermineDirection();
};
