// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/Mimic.h"
#include "Player/PlayerZDChar.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

AMimic::AMimic()
{
    PrimaryActorTick.bCanEverTick = true; // Assicurati che questo sia true

    Status = EMimicStatus::Chest;
    MoveSpeed = 150.0f;
}

void AMimic::BeginPlay()
{
    Super::BeginPlay();

}

void AMimic::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    MoveMimic(DeltaTime);
}

void AMimic::TransformToEnemy()
{
        Status = EMimicStatus::Mimic;

        SetActorEnableCollision(true);
        SetActorTickEnabled(true);

        Health = 100;
        Damage = 20;
        AttackRange = 300.0f;
        AttackCooldown = 1.5f;
        MoveSpeed = 100.0f;

        UCapsuleComponent* Capsule = FindComponentByClass<UCapsuleComponent>();
        if (Capsule)
        {
            Capsule->SetCollisionProfileName(TEXT("Pawn"));
        }

        UE_LOG(LogTemp, Log, TEXT("Il mimic si è trasformato in un nemico!"));
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

            if (FVector::Dist(GetActorLocation(), Player->GetActorLocation()) <= AttackRange)
            {
                PerformMeleeAttack();
            }
        }
    }
}
