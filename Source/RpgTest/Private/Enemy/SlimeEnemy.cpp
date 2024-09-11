// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/SlimeEnemy.h"

ASlimeEnemy::ASlimeEnemy()
{
    Health = 80;
    Damage = 15;
    AttackRange = 100.0f;
    AttackCooldown = 2.0f;
    bIsRanged = false;

    PoisonDamage = 5.f;
}

void ASlimeEnemy::BeginPlay()
{
    Super::BeginPlay();
}

void ASlimeEnemy::PerformMeleeAttack()
{
    UE_LOG(LogTemp, Warning, TEXT("Slime attacks with melee!"));
    
    Super::PerformMeleeAttack();

    if (TargetPlayer)
    {
        TargetPlayer->ApplyState(EPlayerState::Poisoned, PoisonDamage);
    }

}
