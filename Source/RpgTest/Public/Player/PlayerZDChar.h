// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "PlayerZDChar.generated.h"


UENUM(BlueprintType)
enum class FPlayerDirection : uint8
{
	Up,
	Down,
	Left,
	Right
};


UCLASS()
class RPGTEST_API APlayerZDChar : public APaperZDCharacter
{
	GENERATED_BODY()
	
public:

	// Constructor
	APlayerZDChar();

	// Inventory Management
	/** Receives and adds items to the player's inventory. */
	void ReciveItem(class AItem* Item);

	/** Uses a shield potion if available. */
	void UseShieldPotion();

	/** Uses an attack potion if available. */
	void UseAttackPotion();

	// Combat and Damage
	/** Apply damage to the player. */
	void ApplyDamage(int DamageAmount);

	/** Increase the player's shield by the specified amount. */
	void IncreaseShield(float Amount);

	/** Increase the player's attack stat by the specified amount. */
	void IncreaseAttack(float Amount);

	// Player Interaction
	/** Interacts with an interactable actor if within range. */
	void Interact();

	/** Called when another actor overlaps the player. */
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	/** Called when another actor ends overlap with the player. */
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	// Player Stats Management
	/** Returns the current health of the player. */
	UFUNCTION(BlueprintPure, Category = "PlayerStats")
	int GetPlyHealth() const;

	/** Returns the current shield value of the player. */
	UFUNCTION(BlueprintPure, Category = "PlayerStats")
	int GetPlyShield() const;

	/** Called when the player gains experience points (XP). */
	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
	void GainXP(int32 Amount);

	// Room Management
	/** Returns the current room where the player is located. */
	UFUNCTION(BlueprintCallable, Category = "Player")
	ARoom* GetCurrentRoom() const;

	// Movement Variables
	/** Whether the player is currently performing an attack action. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerMovement")
	bool isAttacking;

	/** Direction in which the player is currently facing. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerMovement")
	FPlayerDirection PlyRotation;

	// Inventory Variables
	/** Number of shield potions the player currently has. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	int32 ShieldPotionCount;

	/** Number of attack potions the player currently has. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	int32 AttackPotionCount;

	// Player Stats
	/** Current health of the player. */
	int Health;

	/** Current shield value of the player. */
	int Shield;

	/** Current attack damage of the player. */
	int Damage;

	// Player Interaction
	/** Whether the player can interact with an object. */
	bool bCanInteract;

	/** The interactable actor that the player is near. */
	AActor* InteractableActor;
	// Movement Variables

	/** Component responsible for handling the player's animation. */
	UPaperZDAnimationComponent* AnimationComponent;

	// Experience and Leveling
	/** The player's current level. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerStats")
	int32 PlayerLevel;

	/** The player's current experience points (XP). */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerStats")
	int32 CurrentXP;

	/** The XP required for the player to reach the next level. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerStats")
	int32 XPToNextLevel;

	

	bool bIsMinimapVisible;

	void ManageMinimap();

	void HideMinimap();

protected:

	// Core Functions
	/** Called when the game starts or when the player is spawned. */
	virtual void BeginPlay() override;

	/** Called every frame. */
	virtual void Tick(float DeltaTime) override;

	/** Binds player inputs (movement, attacks, etc.). */
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/** Get the current rotation of the player. */
	FRotator GetRotation();

	/** Move the player forward or backward based on input. */
	void MoveForeward(float AxisValue);

	/** Move the player right or left based on input. */
	void MoveRight(float AxisValue);

	/** Perform the player's attack action. */
	void Attack();

	/** Handle directional movement based on the player's input. */
	void MovePlayer(FVector Direction);

	UFUNCTION(BlueprintCallable, Category = "Level")
	ALevelManager* GetLevelManager() const;

};
