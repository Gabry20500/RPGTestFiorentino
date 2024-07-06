// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

UCLASS()
class RPGTEST_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	FString EnemyType;
	float health;
	float attack;
	float defense;
	FVector position;
	FRotator direction;
	bool bIsAlive;

	virtual void Move(float DeltaTime);
	virtual void Attack();
	virtual void ReceiveDamage(float Damage);
	virtual void Die();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
