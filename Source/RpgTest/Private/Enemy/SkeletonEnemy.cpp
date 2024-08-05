// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/SkeletonEnemy.h"

ASkeletonEnemy::ASkeletonEnemy()
{
    Health = 80;
    Damage = 15;
    AttackRange = 500.0f;
    AttackCooldown = 3.0f;
    bIsRanged = true;
}

void ASkeletonEnemy::BeginPlay()
{
    Super::BeginPlay();
}

void ASkeletonEnemy::PerformRangedAttack()
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
                FVector LaunchDirection = MuzzleRotation.Vector();
                Projectile->SetVelocity(LaunchDirection);
            }
        }
    }
}

void ASkeletonEnemy::DetermineDirection()
{
    if (TargetPlayer)
    {
        FVector DirectionToPlayer = TargetPlayer->GetActorLocation() - GetActorLocation();
        DirectionToPlayer.Z = 0; 

        DirectionToPlayer.Normalize();

        if (FVector::DotProduct(DirectionToPlayer, FVector(1, 0, 0)) > 0.7f)
        {
            CurrentDirection = ESkeletonDirection::Up;
        }
        else if (FVector::DotProduct(DirectionToPlayer, FVector(-1, 0, 0)) > 0.7f)
        {
            CurrentDirection = ESkeletonDirection::Down;
        }
        else if (FVector::DotProduct(DirectionToPlayer, FVector(0, 1, 0)) > 0.7f)
        {
            CurrentDirection = ESkeletonDirection::Right;
        }
        else if (FVector::DotProduct(DirectionToPlayer, FVector(0, -1, 0)) > 0.7f)
        {
            CurrentDirection = ESkeletonDirection::Left;
        }
    }
}
