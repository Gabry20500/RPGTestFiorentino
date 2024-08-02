// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Enemy.h"
#include "SlimeEnemy.generated.h"

/**
 * 
 */
UCLASS()
class RPGTEST_API ASlimeEnemy : public AEnemy
{
	GENERATED_BODY()
	
public:
	ASlimeEnemy();
	
protected:
	virtual void BeginPlay() override;

	virtual void PerformMeleeAttack() override;
};
