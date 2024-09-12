// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/Projectile.h"
#include "Components/SphereComponent.h"
#include <Player/PlayerZDChar.h>

// Sets default values
AProjectile::AProjectile()
{
    // Enable ticking for this actor
    PrimaryActorTick.bCanEverTick = true;

    // Create and initialize the projectile movement component
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->InitialSpeed = 1000.0f;  // Initial speed of the projectile
    ProjectileMovement->MaxSpeed = 1000.0f;     // Maximum speed of the projectile
}

void AProjectile::SetDamage(float InDamage)
{
    // Set the damage value for the projectile
    Damage = InDamage;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
    Super::BeginPlay();

    // Find the sphere component and bind overlap event
    USphereComponent* SphereComponent = FindComponentByClass<USphereComponent>();
    if (SphereComponent)
    {
        // Bind the overlap event to the OnOverlapBegin function
        SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
    }
}

void AProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("%s"), *OverlappedComp->GetName());

    // Check if the overlapped actor is valid and is not the projectile itself or its owner
    if (OtherActor && OtherActor != this && OtherActor != GetOwner())
    {
        // Check if the actor has the "Player" tag
        if (OtherActor->ActorHasTag(FName("Player")))
        {
            // Cast the actor to APlayerZDChar and apply damage if successful
            APlayerZDChar* Player = Cast<APlayerZDChar>(OtherActor);
            if (Player)
            {
                Player->ApplyDamage(Damage);
            }
        }

        // Destroy the projectile after the impact
        Destroy();
    }
}

void AProjectile::SetVelocity(const FVector& Direction)
{
    // Set the projectile's velocity based on the given direction
    if (ProjectileMovement)
    {
        ProjectileMovement->Velocity = Direction * ProjectileMovement->InitialSpeed;
    }
}

