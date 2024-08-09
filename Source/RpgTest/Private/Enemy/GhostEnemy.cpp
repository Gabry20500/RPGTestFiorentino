// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/GhostEnemy.h"

AGhostEnemy::AGhostEnemy()
{
    Health = 60;
    Damage = 10;
    AttackRange = 2000.0f;
    AttackCooldown = 2.5f;
    bIsRanged = true;
}

void AGhostEnemy::BeginPlay()
{
    Super::BeginPlay();
}

void AGhostEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsChasingPlayer)
    {
        MoveToPlayer();
        CheckAttackRange();
        DetermineDirection();
    }
}

void AGhostEnemy::PerformRangedAttack()
{
    if (TargetPlayer && ProjectileClass)
    {
        FVector MuzzleLocation = GetActorLocation() + FVector(0, 0, 50); // Posizione da cui parte il proiettile
        FRotator MuzzleRotation = (TargetPlayer->GetActorLocation() - MuzzleLocation).Rotation();

        UWorld* World = GetWorld();
        if (World)
        {
            AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation);
            if (Projectile)
            {
                Projectile->SetDamage(Damage);

                FVector LaunchDirection = MuzzleRotation.Vector();
                Projectile->SetVelocity(LaunchDirection);
            }
        }
    }
}

void AGhostEnemy::DetermineDirection()
{
    if (TargetPlayer)
    {
        FVector DirectionToPlayer = TargetPlayer->GetActorLocation() - GetActorLocation();
        DirectionToPlayer.Z = 0;

        DirectionToPlayer.Normalize();

        if (FVector::DotProduct(DirectionToPlayer, FVector(1, 0, 0)) > 0.7f)
        {
            CurrentDirection = EGhostDirection::Up;
        }
        else if (FVector::DotProduct(DirectionToPlayer, FVector(-1, 0, 0)) > 0.7f)
        {
            CurrentDirection = EGhostDirection::Down;
        }
        else if (FVector::DotProduct(DirectionToPlayer, FVector(0, 1, 0)) > 0.7f)
        {
            CurrentDirection = EGhostDirection::Right;
        }
        else if (FVector::DotProduct(DirectionToPlayer, FVector(0, -1, 0)) > 0.7f)
        {
            CurrentDirection = EGhostDirection::Left;
        }
    }
}
