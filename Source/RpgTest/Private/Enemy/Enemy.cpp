// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Enemy.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Health = 100;
    Damage = 20;
    AttackRange = 100.0f; 
    AttackCooldown = 2.0f;
    bIsRanged = false;
    bIsChasingPlayer = false;
    bCanAttack = true;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

    APlayerZDChar* PlayerCharacter = Cast<APlayerZDChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    if (PlayerCharacter)
    {
        TargetPlayer = PlayerCharacter;
        if (TargetPlayer)
        {
            bIsChasingPlayer = true;
        }
    }
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (bIsChasingPlayer)
    {
        MoveToPlayer();
        CheckAttackRange();
    }
}

void AEnemy::ApplyDamage(int DamageAmount)
{
    Health -= DamageAmount;

    // Check if health has dropped to zero or below
    if (Health <= 0)
    {
        Health = 0;
        // Handle actor's death (could be destroying the actor or playing a death animation)
        Destroy(); // For now, we'll just destroy the actor
    }

    UE_LOG(LogTemp, Log, TEXT("%d"), Health);
}

void AEnemy::MoveToPlayer()
{
    if (TargetPlayer)
    {
        AAIController* AIController = Cast<AAIController>(GetController());
        if (AIController)
        {
            AIController->MoveToActor(TargetPlayer);
        }
    }
}

void AEnemy::CheckAttackRange()
{
    if (TargetPlayer && bCanAttack)
    {
        float DistanceToPlayer = FVector::Dist(GetActorLocation(), TargetPlayer->GetActorLocation());

        if (DistanceToPlayer <= AttackRange)
        {
            if (bIsRanged)
            {
                PerformRangedAttack();
            }
            else
            {
                PerformMeleeAttack();
            }

            StartAttackCooldown();
        }
    }
}

void AEnemy::StartAttackCooldown()
{
    bCanAttack = false;

    GetWorldTimerManager().SetTimer(
        AttackCooldownTimerHandle,
        this,
        &AEnemy::ResetAttack,
        AttackCooldown,
        false
    );
}

void AEnemy::ResetAttack()
{
    bCanAttack = true;
}

void AEnemy::PerformMeleeAttack()
{
    UE_LOG(LogTemp, Warning, TEXT("Base Melee Attack!"));
    TargetPlayer->ApplyDamage(Damage);
}

void AEnemy::PerformRangedAttack()
{
    if (TargetPlayer)
    {
        UE_LOG(LogTemp, Warning, TEXT("Ranged Attack!"));

        // Imposta il ritardo per l'applicazione del danno
        GetWorldTimerManager().SetTimer(
            DamageDelayTimerHandle,
            this,
            &AEnemy::ApplyDamageWithDelay,
            2.0f, // Ritardo di 2 secondi
            false
        );
    }
}

void AEnemy::ApplyDamageWithDelay()
{
    if(TargetPlayer) TargetPlayer->ApplyDamage(Damage);
}

