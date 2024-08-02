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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void ApplyDamage(int DamageAmount);

	UFUNCTION()
	void OnPlayerDetected(APawn* DetectedPawn);

protected:
    void MoveToPlayer();

    void CheckAttackRange();

    virtual void PerformMeleeAttack();
    virtual void PerformRangedAttack();

    // Componenti e variabili
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    class UPawnSensingComponent* PawnSensingComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float AttackRange;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    bool bIsChasingPlayer;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    APawn* TargetPlayer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    bool bIsRanged;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EnemyHealth")
    int Health = 0;
};
