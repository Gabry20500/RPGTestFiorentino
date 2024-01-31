// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */

UCLASS()
class RPGTESTFIORENTINO_API APlayerCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:

	// Function to handle moving forward/backward
	UFUNCTION()
	void MoveForward(float Value);

	// Function to handle moving left/right
	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void Attack();

	UFUNCTION()
	void StopAttack();

	UFUNCTION()
	void Defend();

	UFUNCTION()
	void StopDefend();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimationDirection")
	int Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BasicAttack")
	bool IsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BasicAttack")
	bool IsDefending;
};
