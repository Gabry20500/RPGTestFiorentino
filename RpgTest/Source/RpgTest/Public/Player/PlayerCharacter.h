// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemies/Enemy.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class RPGTEST_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	float health;
    float attack;
    float defense;
    FVector position;
    FRotator direction;
    bool bIsAlive;

    // Funzioni di movimento e attacco (come nel precedente esempio)

	void Move(float DeltaTime);
	void Attack(AEnemy* Target);
    void ActivateShield();
    void ReceiveDamage(float Damage);
    void Die();
    
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    private:
        // Variabile per indicare se lo scudo è attivo
        bool bShieldActive;

};
