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

    PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
    PawnSensingComponent->OnSeePawn.AddDynamic(this, &AEnemy::OnPlayerDetected);

    AttackRange = 200.0f; 
    bIsRanged = false;
    Health = 100;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
    if (bIsChasingPlayer)
    {
        MoveToPlayer();
        CheckAttackRange();
    }
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

void AEnemy::OnPlayerDetected(APawn* DetectedPawn)
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController && DetectedPawn == PlayerController->GetPawn())
    {
        bIsChasingPlayer = true;
        TargetPlayer = DetectedPawn;
    }

}

void AEnemy::MoveToPlayer()
{
}

void AEnemy::CheckAttackRange()
{
}

void AEnemy::PerformMeleeAttack()
{
}

void AEnemy::PerformRangedAttack()
{
}

