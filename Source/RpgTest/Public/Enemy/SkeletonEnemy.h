// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Enemy.h"
#include "Projectile/Projectile.h"
#include "SkeletonEnemy.generated.h"


UENUM(BlueprintType)
enum class ESkeletonDirection : uint8
{
	Up UMETA(DisplayName = "Up"),
	Down UMETA(DisplayName = "Down"),
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right")
};

/**
 * 
 */
UCLASS()
class RPGTEST_API ASkeletonEnemy : public AEnemy
{
	GENERATED_BODY()
	
public:
	ASkeletonEnemy();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void PerformRangedAttack() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skeleton", meta = (AllowPrivateAccess = "true"))
	ESkeletonDirection CurrentDirection;

	void DetermineDirection();

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;
};
