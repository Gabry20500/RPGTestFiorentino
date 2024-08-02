// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Player/PlayerZDChar.h"
#include "Enemy.generated.h"

UCLASS()
class RPGTEST_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void ApplyDamage(int DamageAmount);

protected:
    void MoveToPlayer();

    void CheckAttackRange();

    void StartAttackCooldown();

    void ResetAttack();

    virtual void PerformMeleeAttack();
    virtual void PerformRangedAttack();

    void ApplyDamageWithDelay();

    // Componenti e variabili
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    class UPawnSensingComponent* PawnSensingComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float AttackRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float AttackCooldown;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    bool bCanAttack;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    bool bIsChasingPlayer;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    APlayerZDChar* TargetPlayer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    bool bIsRanged;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EnemyHealth")
    int Health;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EnemyHealth")
    int Damage;

    FTimerHandle AttackCooldownTimerHandle;
    FTimerHandle DamageDelayTimerHandle;
};
