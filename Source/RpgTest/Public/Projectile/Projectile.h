// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include "Projectile.generated.h"

/**
 * AProjectile represents a projectile in the game, such as a missile or a bullet.
 * It handles its movement, damage, and collision behavior.
 */
UCLASS()
class RPGTEST_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	/**
	 * Sets the damage dealt by this projectile.
	 * @param InDamage The damage value to assign.
	 */
	void SetDamage(float InDamage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

    /**
     * Handles the overlap event when this projectile collides with another actor.
     * @param OverlappedComp The component that triggered the overlap event.
     * @param OtherActor The actor that this projectile has overlapped with.
     * @param OtherComp The component of the other actor that was overlapped.
     * @param OtherBodyIndex The index of the body in the overlap event.
     * @param bFromSweep Whether the overlap was from a sweep.
     * @param SweepResult The result of the sweep.
     */
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    /**
     * Sets the velocity of the projectile in the specified direction.
     * @param Direction The direction to set the projectile's velocity.
     */
    void SetVelocity(const FVector& Direction);

private:

    // Projectile movement component to handle the projectile's motion
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    class UProjectileMovementComponent* ProjectileMovement;

    // The damage dealt by the projectile
    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    float Damage = 20.0f;
};
