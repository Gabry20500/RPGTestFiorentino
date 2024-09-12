// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player/PlayerZDChar.h"
#include "PaperFlipbookComponent.h"
#include "HealthFountain.generated.h"

/**
 * AHealthFountain represents a health fountain in the game that provides healing to the player.
 * It can display different animations when used and has a mechanism to heal the player character.
 */
UCLASS()
class RPGTEST_API AHealthFountain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Constructor: Sets default values for this actor's properties
	AHealthFountain();

protected:
	// BeginPlay: Called when the game starts or when the actor is spawned
	virtual void BeginPlay() override;

public:
	// Tick: Called every frame to update the actor
	virtual void Tick(float DeltaTime) override;

	/**
	 * HealPlayer: Heals the specified player character by the amount defined in HealAmount.
	 * @param PlayerCharacter - The player character to heal.
	 */
	void HealPlayer(APlayerZDChar* PlayerCharacter);

	/** The amount of health to be restored by the fountain */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Healing")
	float HealAmount;

	/**
	 * ChangeFlipbook: Changes the flipbook animation to indicate that the fountain has been used.
	 */
	void ChangeFlipbook();

private:
	/** The component responsible for displaying the flipbook animation */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* FlipbookComponent;

	/** The flipbook animation to display after the fountain has been used */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fountain", meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* UsedFlipbook;

	/** Flag to track if the fountain has been used */
	bool IsUsed;
};
