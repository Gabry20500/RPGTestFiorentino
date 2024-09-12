// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Enemy.h"
#include "SlimeEnemy.generated.h"

/**
 * ASlimeEnemy: Represents a slime-type enemy in the game.
 * This enemy has melee attacks and deals additional poison damage to the player.
 */
UCLASS()
class RPGTEST_API ASlimeEnemy : public AEnemy
{
	GENERATED_BODY()
	
public:
	// Constructor: Sets default values specific to the Slime enemy.
	ASlimeEnemy();
	
protected:
	// Called when the game starts or when spawned.
	virtual void BeginPlay() override;

	// Overrides the base melee attack to add custom behavior for the Slime enemy.
	virtual void PerformMeleeAttack() override;

	// Poison damage dealt on top of the normal melee attack.
	float PoisonDamage;
};
