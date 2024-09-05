// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/Mimic.h"
#include "Player/PlayerZDChar.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

AMimic::AMimic()
{
    PrimaryActorTick.bCanEverTick = true;

    Status = EMimicStatus::Chest;
    MoveSpeed = 150.0f;
    bIsChasingPlayer = false;
}

void AMimic::BeginPlay()
{
    Super::BeginPlay();

}

void AMimic::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (Status == EMimicStatus::Mimic)
    {
        MoveMimic(DeltaTime);
    }
    else 
    {
        bIsChasingPlayer = false;
    }
}

void AMimic::TransformToEnemy()
{
    Status = EMimicStatus::Mimic;

    SetActorEnableCollision(true);
    SetActorTickEnabled(true);

    Health = 100;
    Damage = 20;
    AttackRange = 80.0f;
    AttackCooldown = 3.f;
    MoveSpeed = 50.0f;

    // Ora inizia a inseguire il giocatore
    bIsChasingPlayer = true;

    UCapsuleComponent* Capsule = FindComponentByClass<UCapsuleComponent>();
    if (Capsule)
    {
        Capsule->SetCollisionProfileName(TEXT("Pawn"));
    }

    UE_LOG(LogTemp, Warning, TEXT("Il mimic si è trasformato in un nemico!"));
}


void AMimic::DetermineDirection()
{
    if (Status == EMimicStatus::Mimic)
    {
        APlayerZDChar* Player = Cast<APlayerZDChar>(UGameplayStatics::GetPlayerCharacter(this, 0));
        if (Player)
        {
            FVector DirectionToPlayer = Player->GetActorLocation() - GetActorLocation();
            DirectionToPlayer.Z = 0;
            DirectionToPlayer.Normalize();

            if (FVector::DotProduct(DirectionToPlayer, FVector(1, 0, 0)) > 0.7f)
            {
                CurrentDirection = EMimicDirection::Right;
            }
            else if (FVector::DotProduct(DirectionToPlayer, FVector(-1, 0, 0)) > 0.7f)
            {
                CurrentDirection = EMimicDirection::Left;
            }
            else if (FVector::DotProduct(DirectionToPlayer, FVector(0, 1, 0)) > 0.7f)
            {
                CurrentDirection = EMimicDirection::Up;
            }
            else if (FVector::DotProduct(DirectionToPlayer, FVector(0, -1, 0)) > 0.7f)
            {
                CurrentDirection = EMimicDirection::Down;
            }
        }
    }
}

void AMimic::MoveMimic(float Time)
{
    if (Status == EMimicStatus::Mimic)
    {
        APlayerZDChar* Player = Cast<APlayerZDChar>(UGameplayStatics::GetPlayerCharacter(this, 0));
        if (Player)
        {
            FVector DirectionToPlayer = Player->GetActorLocation() - GetActorLocation();
            DirectionToPlayer.Z = 0;
            DirectionToPlayer.Normalize();

            DetermineDirection();

            SetActorLocation(GetActorLocation() + DirectionToPlayer * MoveSpeed * Time);

            float DistanceToPlayer = FVector::Dist(GetActorLocation(), Player->GetActorLocation());

            // Attacca solo se è nella distanza corretta e può attaccare
            if (DistanceToPlayer <= AttackRange && bCanAttack)
            {
                PerformMeleeAttack();
                StartAttackCooldown();  // Inizia il cooldown dopo l'attacco
            }
        }
    }
}
