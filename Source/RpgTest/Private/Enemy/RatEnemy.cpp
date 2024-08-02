// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/RatEnemy.h"
#include "Kismet/GameplayStatics.h"


ARatEnemy::ARatEnemy()
{
    Health = 50;
    Damage = 10;
    AttackRange = 50.0f;
    AttackCooldown = 1.5f;
    bIsRanged = false;
}

void ARatEnemy::BeginPlay()
{
    Super::BeginPlay();
}

void ARatEnemy::PerformMeleeAttack()
{
    UE_LOG(LogTemp, Warning, TEXT("Rat attacks with melee!"));
    // Chiamata al metodo base
    Super::PerformMeleeAttack();
}

void ARatEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsChasingPlayer)
    {
        MoveToPlayer();
        CheckAttackRange();
        DetermineDirection();
    }
}

void ARatEnemy::DetermineDirection()
{
    if (TargetPlayer)
    {
        FVector DirectionToPlayer = TargetPlayer->GetActorLocation() - GetActorLocation();
        DirectionToPlayer.Z = 0;
        DirectionToPlayer.Normalize();


        if (FVector::DotProduct(DirectionToPlayer, FVector(1, 0, 0)) > 0.7f)
        {
            CurrentDirection = ERatDirection::Up;
        }
        else if (FVector::DotProduct(DirectionToPlayer, FVector(-1, 0, 0)) > 0.7f)
        {
            CurrentDirection = ERatDirection::Down;
        }
        else if (FVector::DotProduct(DirectionToPlayer, FVector(0, 1, 0)) > 0.7f)
        {
            CurrentDirection = ERatDirection::Right;
        }
        else if (FVector::DotProduct(DirectionToPlayer, FVector(0, -1, 0)) > 0.7f)
        {
            CurrentDirection = ERatDirection::Left;
        }
    }
}
