// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "PlayerZDChar.generated.h"


// Enumeration for defining player movement directions
UENUM(BlueprintType)
enum class FPlayerDirection : uint8
{
	Up,
	Down,
	Left,
	Right
};

// Enumeration for defining various player states with display names for UI
UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	Normal UMETA(DisplayName = "Normal"),
	Poisoned UMETA(DisplayName = "Poisoned"),
	Burning UMETA(DisplayName = "Burning")
};

// APlayerZDChar class definition
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
    /** Applies damage to the player. */
    void ApplyDamage(int DamageAmount);

    /** Increases the player's shield by the specified amount. */
    void IncreaseShield(float Amount);

    /** Increases the player's attack stat by the specified amount. */
    void IncreaseAttack(float Amount);

    // Player Interaction
    /** Interacts with an interactable actor if within range. */
    void Interact();

    /** Called when another actor overlaps with the player. */
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

    /** The current state of the player (e.g., Normal, Poisoned, Burning). */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player State")
    EPlayerState CurrentState;

    /** Applies a new state to the player. */
    void ApplyState(EPlayerState NewState, float StateDuration);

    /** Timer handle for managing state duration and effects. */
    FTimerHandle StateTimerHandle;
    float PoisonDuration;
    float BurningDuration;

    /** Whether the minimap is currently visible. */
    bool bIsMinimapVisible;

    /** Manages minimap visibility and updates. */
    void ManageMinimap();

    /** Hides the minimap. */
    void HideMinimap();

protected:

    // Core Functions
    /** Called when the game starts or when the player is spawned. */
    virtual void BeginPlay() override;

    /** Binds player inputs (movement, attacks, etc.). */
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    /** Retrieves the current rotation of the player. */
    FRotator GetRotation();

    /** Moves the player forward or backward based on input. */
    void MoveForeward(float AxisValue);

    /** Moves the player right or left based on input. */
    void MoveRight(float AxisValue);

    /** Performs the player's attack action. */
    void Attack();

    /** Handles directional movement based on the player's input. */
    void MovePlayer(FVector Direction);

    /** Retrieves the level manager instance. */
    UFUNCTION(BlueprintCallable, Category = "Level")
    ALevelManager* GetLevelManager() const;

    /** Updates the player's color based on certain conditions. */
    void UpdatePlayerColor();

    // Functions for managing damage and states
    /** Handles periodic damage application for the poisoned state. */
    void PoisonTick();

    /** Handles periodic damage application for the burning state. */
    void BurnTick();

    /** Clears the current state effects from the player. */
    void ClearState();

    /** Component for handling player flipbook animations. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    class UPaperFlipbookComponent* PlayerFlipbook;
};
