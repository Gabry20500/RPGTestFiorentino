// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/Projectile.h"
#include "Components/SphereComponent.h"
#include <Player/PlayerZDChar.h>

// Sets default values
AProjectile::AProjectile()
{
    PrimaryActorTick.bCanEverTick = true;

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->InitialSpeed = 1000.0f;
    ProjectileMovement->MaxSpeed = 1000.0f;

}

void AProjectile::SetDamage(float InDamage)
{
    Damage = InDamage;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

    USphereComponent* SphereComponent = FindComponentByClass<USphereComponent>();
    if (SphereComponent)
    {
        SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
    }
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("%s"), *OverlappedComp->GetName());
    if (OtherActor && OtherActor != this && OtherActor != GetOwner())
    {
        // Controlla se l'attore colpito ha il tag "Player"
        if (OtherActor->ActorHasTag(FName("Player")))
        {
            // Cast dell'attore a APlayerZDChar
            APlayerZDChar* Player = Cast<APlayerZDChar>(OtherActor);
            if (Player)
            {
                // Applica il danno al giocatore
                Player->ApplyDamage(Damage);
            }
        }

        // Distruggi il proiettile dopo l'impatto
        Destroy();
    }
}

void AProjectile::SetVelocity(const FVector& Direction)
{
    if (ProjectileMovement)
    {
        ProjectileMovement->Velocity = Direction * ProjectileMovement->InitialSpeed;
    }
}

