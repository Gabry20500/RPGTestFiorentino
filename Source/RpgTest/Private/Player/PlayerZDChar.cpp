// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerZDChar.h"
#include "PaperZDAnimationComponent.h"
#include "PaperZDAnimInstance.h"
#include <Enemy/Enemy.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Interactable/HealthFountain.h>
#include <Interactable/Chest.h>
#include <Interactable/Mimic.h>
#include <RoomGeneration/Door.h>
#include <RoomGeneration/Room.h>
#include <RoomGeneration/LevelManager.h>
#include <Kismet/GameplayStatics.h>
#include "Item/AttackPotion.h"
#include "Item/ShieldPotion.h"
#include "Blueprint/UserWidget.h"
#include "Minimap/Minimap.h"
#include <Kismet/GameplayStatics.h>


// Constructor: Initializes default values for the player's attributes
APlayerZDChar::APlayerZDChar()
{
    // Allow the actor to tick every frame
    PrimaryActorTick.bCanEverTick = true;

    // Set default values for attributes
    Damage = 35;
    Health = 100;
    Shield = 0;

    bCanInteract = false;
    InteractableActor = nullptr;
    bIsMinimapVisible = false;

    PlayerLevel = 1;
    CurrentXP = 0;
    XPToNextLevel = 100;

    AttackPotionCount = 0;
    ShieldPotionCount = 0;
}

// Increases the player's XP and handles level-up logic
void APlayerZDChar::GainXP(int32 Amount)
{
    // Increment XP and log the amount gained
    CurrentXP += Amount;
    UE_LOG(LogTemp, Log, TEXT("XP Gained: %d, Current XP: %d"), Amount, CurrentXP);

    // Check if the player has reached the XP threshold for leveling up
    if (CurrentXP >= XPToNextLevel)
    {
        // Handle level-up
        CurrentXP -= XPToNextLevel;
        PlayerLevel++;
        XPToNextLevel += 50; // Increase XP required for the next level

        UE_LOG(LogTemp, Warning, TEXT("Level Up! New Level: %d | Next Level XP: %d | Current XP : %d"), PlayerLevel, XPToNextLevel, CurrentXP);

        // Enhance player's health and damage upon leveling up
        Health += 20;
        Damage += 5;
    }
}

// Returns the current health of the player
int APlayerZDChar::GetPlyHealth() const
{
    return Health;
}

// Returns the current shield value of the player
int APlayerZDChar::GetPlyShield() const
{
    return Shield;
}

// Increases the player's shield value by the specified amount
void APlayerZDChar::IncreaseShield(float Amount)
{
    Shield += Amount;
}

// Increases the player's attack damage by the specified amount
void APlayerZDChar::IncreaseAttack(float Amount)
{
    Damage += Amount;
}

// Applies a new state to the player and sets up timers for state effects
void APlayerZDChar::ApplyState(EPlayerState NewState, float StateDuration)
{
    CurrentState = NewState;

    UpdatePlayerColor(); // Update player color based on the new state

    // Set up timers for state effects based on the new state
    switch (CurrentState)
    {
    case EPlayerState::Poisoned:
        PoisonDuration = StateDuration;
        GetWorldTimerManager().SetTimer(StateTimerHandle, this, &APlayerZDChar::PoisonTick, 1.0f, true);
        break;
    case EPlayerState::Burning:
        BurningDuration = StateDuration;
        GetWorldTimerManager().SetTimer(StateTimerHandle, this, &APlayerZDChar::BurnTick, 1.0f, true);
        break;
    default:
        break;
    }
}

// Toggle the minimap visibility
void APlayerZDChar::ManageMinimap()
{
    if (bIsMinimapVisible == false)
    {
        if (ALevelManager* LevelManager = GetLevelManager())
        {
            LevelManager->ToggleMinimap(true);
            bIsMinimapVisible = true;
        }
    }
    else
    {
        if (ALevelManager* LevelManager = GetLevelManager())
        {
            LevelManager->ToggleMinimap(false);
            bIsMinimapVisible = false;
        }
    }
}

// Hide the minimap
void APlayerZDChar::HideMinimap()
{
    if (ALevelManager* LevelManager = GetLevelManager())
    {
        LevelManager->ToggleMinimap(false);
    }
}

// Initializes components and default values when the game starts
void APlayerZDChar::BeginPlay()
{
    Super::BeginPlay();

    // Initialize animation components and flipbook
    AnimationComponent = Cast<UPaperZDAnimationComponent>(GetComponentByClass(UPaperZDAnimationComponent::StaticClass()));
    PlayerFlipbook = FindComponentByClass<UPaperFlipbookComponent>();

    // Set default player rotation
    PlyRotation = FPlayerDirection::Down;
}

// Bind input actions and axes for player control
void APlayerZDChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Bind movement and action inputs
	InputComponent->BindAxis("MoveRight", this, &APlayerZDChar::MoveRight);
	InputComponent->BindAxis("MoveForeward", this, &APlayerZDChar::MoveForeward);
	InputComponent->BindAction("Attack", IE_Pressed, this, &APlayerZDChar::Attack);
    InputComponent->BindAction("Interact", IE_Pressed, this, &APlayerZDChar::Interact);

    InputComponent->BindAction("UseShieldPotion", IE_Pressed, this, &APlayerZDChar::UseShieldPotion);
    InputComponent->BindAction("UseAttackPotion", IE_Pressed, this, &APlayerZDChar::UseAttackPotion);

    InputComponent->BindAction("ToggleMinimap", IE_Pressed, this, &APlayerZDChar::ManageMinimap);

}

// Return the player's rotation based on the direction
FRotator APlayerZDChar::GetRotation()
{
    switch (PlyRotation)
    {
    case FPlayerDirection::Up:
        return FRotator(0.f, 0.f, 0.f);
        break;
    case FPlayerDirection::Down:
        return FRotator(180.f, 0.f, 0.f);
        break;
    case FPlayerDirection::Left:
        return FRotator(0.f, -90.f, 0.f);
        break;
    case FPlayerDirection::Right:
        return FRotator(0.f, 90.f, 0.f);
        break;
    default:
        return FRotator(180.f, 0.f, 0.f);
        break;
    }
}

// Move the player forward or backward based on input
void APlayerZDChar::MoveForeward(float AxisValue)
{
    if (AxisValue != 0)
    {
        FVector Dir = FVector(1.f, 0.f, 0.f);
        AddMovementInput(Dir, AxisValue);
        if (AxisValue > 0)
        {
            PlyRotation = FPlayerDirection::Up;
        }
        else
        {
            PlyRotation = FPlayerDirection::Down;
        }
    }
}

// Move the player right or left based on input
void APlayerZDChar::MoveRight(float AxisValue)
{
    if (AxisValue != 0)
    {

        FVector Dir = FVector(0.f, 1.f, 0.f);
        AddMovementInput(Dir, AxisValue);
        if (AxisValue > 0)
        {
            PlyRotation = FPlayerDirection::Right;
        }
        else
        {
            PlyRotation = FPlayerDirection::Left;
        }
    }
}

// Performs an attack and applies damage to enemies within range
void APlayerZDChar::Attack()
{
    APlayerController* PlayerController = Cast<APlayerController>(GetController());
    if (PlayerController)
    {
        isAttacking = true;
        FVector Location = GetActorLocation();
        FRotator Rotation = GetActorRotation();

        FVector Start = Location;
        FVector End = Start + (GetRotation().Vector() * 300.0f);

        FHitResult HitResult;
        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(this);

        // Perform a line trace to detect enemies
        bool bHit = GetWorld()->LineTraceSingleByChannel(
            HitResult,
            Start,
            End,
            ECC_GameTraceChannel1, // Custom enemy trace channel
            CollisionParams
        );

        if (bHit)
        {
            if (AEnemy* Enemy = Cast<AEnemy>(HitResult.GetActor()))
            {
                Enemy->ApplyDamage(Damage);
                UE_LOG(LogTemp, Warning, TEXT("Enemy: %s | Health: %d"), *Enemy->GetName(), Enemy->GetHealth());
            }
        }
    }
}

// Moves the player to a new location and updates the level manager with the new coordinates
void APlayerZDChar::MovePlayer(FVector Direction)
{
    FVector NewLocation = GetActorLocation() + Direction;
    SetActorLocation(NewLocation);

    // Update room coordinates in the LevelManager
    ALevelManager* LevelManager = GetLevelManager();
    if (LevelManager)
    {
        int32 NewX = FMath::RoundToInt(NewLocation.X / 1500.0f);
        int32 NewY = FMath::RoundToInt(NewLocation.Y / 1500.0f);
        LevelManager->MovePlayer(NewX, NewY);
    }

    UE_LOG(LogTemp, Warning, TEXT("Player moved to: %s"), *NewLocation.ToString());
}

// Retrieve the LevelManager instance from the world
ALevelManager* APlayerZDChar::GetLevelManager() const
{
    return Cast<ALevelManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ALevelManager::StaticClass()));
}

// Update the player's color based on the current state
void APlayerZDChar::UpdatePlayerColor()
{
    switch (CurrentState)
    {
    case EPlayerState::Poisoned:
        PlayerFlipbook->SetSpriteColor(FLinearColor::Green);
        break;
    case EPlayerState::Burning:
        PlayerFlipbook->SetSpriteColor(FLinearColor::Red);
        break;
    case EPlayerState::Normal:
    default:
        PlayerFlipbook->SetSpriteColor(FLinearColor::White);
        break;
    }
}

// Applies poison damage to the player every second and decreases the poison duration.
// Removes the poisoned state when the duration expires.
void APlayerZDChar::PoisonTick()
{
    ApplyDamage(5);  // Apply poison damage of 5 units per second
    PoisonDuration -= 1.0f;  // Decrease the poison duration by 1 second

    if (PoisonDuration <= 0.0f)
    {
        // Remove the poisoned state when duration reaches zero or less
        ClearState();
    }
}

// Applies burning damage to the player every second and decreases the burning duration.
// Removes the burning state when the duration expires.
void APlayerZDChar::BurnTick()
{
    ApplyDamage(10);  // Apply burning damage of 10 units per second
    BurningDuration -= 1.0f;  // Decrease the burning duration by 1 second

    if (BurningDuration <= 0.0f)
    {
        // Remove the burning state when duration reaches zero or less
        ClearState();
    }
}

// Clears the player's state, stopping any active timers and resetting the state to normal.
// Updates the player's color to reflect the normal state.
void APlayerZDChar::ClearState()
{
    GetWorldTimerManager().ClearTimer(StateTimerHandle);  // Clear any active state timer
    CurrentState = EPlayerState::Normal;  // Set the player's state to normal
    UpdatePlayerColor();  // Update the player's color to reflect the normal state
}

// Uses a shield potion if available, increasing the player's shield and decrementing the potion count.
// Logs the usage and current shield status.
void APlayerZDChar::UseShieldPotion()
{
    if (ShieldPotionCount > 0)
    {
        IncreaseShield(50.0f);  // Increase the shield value by 50 units
        ShieldPotionCount--;  // Decrease the potion count
        UE_LOG(LogTemp, Log, TEXT("Shield potion used. Current shield: %d | Potions remaining: %d"), Shield, ShieldPotionCount);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No shield potions available!"));  // Log a warning if no potions are left
    }
}

// Uses an attack potion if available, increasing the player's attack damage and decrementing the potion count.
// Logs the usage and current attack damage.
void APlayerZDChar::UseAttackPotion()
{
    if (AttackPotionCount > 0)
    {
        IncreaseAttack(10);  // Increase the attack damage by 10 units
        AttackPotionCount--;  // Decrease the potion count
        UE_LOG(LogTemp, Log, TEXT("Attack potion used! Current attack: %d | Potions remaining: %d"), Damage, AttackPotionCount);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No attack potions available!"));  // Log a warning if no potions are left
    }
}

// Applies damage to the player, first absorbing it with the shield if available.
// Decreases health if the damage exceeds the shield's capacity and logs the remaining health.
void APlayerZDChar::ApplyDamage(int DamageAmount)
{
    UE_LOG(LogTemp, Log, TEXT("Applying Damage: %d"), DamageAmount);  // Log the damage being applied

    // If the player has a shield, absorb the damage with the shield first
    if (Shield > 0)
    {
        if (DamageAmount <= Shield)
        {
            // Damage is less than or equal to the shield value, so only reduce the shield
            Shield -= DamageAmount;
            UE_LOG(LogTemp, Log, TEXT("Damage absorbed by shield. Remaining shield: %d"), Shield);
        }
        else
        {
            // Damage exceeds the shield value, so absorb remaining damage with health
            int32 RemainingDamage = DamageAmount - Shield;
            Shield = 0;  // Deplete the shield
            UE_LOG(LogTemp, Log, TEXT("Shield depleted. Remaining damage to health: %d"), RemainingDamage);

            // Reduce health by the remaining damage
            Health -= RemainingDamage;
        }
    }
    else
    {
        // If no shield is present, apply all damage to health
        Health -= DamageAmount;
    }

    UE_LOG(LogTemp, Log, TEXT("Remaining health: %d"), Health);  // Log the remaining health

    // If health drops to zero or below, consider the player dead
    if (Health <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player is dead!"));  // Log a warning about the player's death
        // Implement logic for player death, such as playing a death animation or changing state
    }
}

// Handles interactions with various types of actors (HealthFountain, Chest, Mimic, Door) based on overlap events.
// Updates the player's ability to interact and logs the interaction status.
void APlayerZDChar::Interact()
{
    if (bCanInteract && InteractableActor)
    {
        if (AHealthFountain* Fountain = Cast<AHealthFountain>(InteractableActor))
        {
            Fountain->HealPlayer(this);  // Heal the player using the health fountain
            Fountain->ChangeFlipbook();  // Change the visual representation of the fountain
        }
        else if (AChest* Chest = Cast<AChest>(InteractableActor))
        {
            Chest->ChangeFlipbook();  // Change the visual representation of the chest
            Chest->GiveItemToPlayer(this);  // Give the item from the chest to the player
        }
        else if (AMimic* Mimic = Cast<AMimic>(InteractableActor))
        {
            Mimic->TransformToEnemy();  // Transform the mimic into an enemy
        }
        else if (ADoor* Door = Cast<ADoor>(InteractableActor))
        {
            ARoom* CurrentRoom = GetCurrentRoom();  // Retrieve the player's current room
            ARoom* NextRoom = Door->GetLinkedRoom();  // Retrieve the room linked by the door

            if (CurrentRoom && NextRoom)
            {
                // Determine the direction of movement based on the door
                FVector Direction;
                if (Door == CurrentRoom->NorthDoor)
                {
                    Direction = FVector(300.0f, 0, 0);  // Move north
                }
                else if (Door == CurrentRoom->SouthDoor)
                {
                    Direction = FVector(-300.0f, 0, 0);  // Move south
                }
                else if (Door == CurrentRoom->EastDoor)
                {
                    Direction = FVector(0, 300.0f, 0);  // Move east
                }
                else if (Door == CurrentRoom->WestDoor)
                {
                    Direction = FVector(0, -300.0f, 0);  // Move west
                }

                MovePlayer(Direction);  // Move the player in the determined direction

                // Find the LevelManager and update the current room
                TArray<AActor*> FoundActors;
                UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("LM"), FoundActors);

                for (AActor* Actor : FoundActors)
                {
                    ALevelManager* LevelManager = Cast<ALevelManager>(Actor);
                    if (LevelManager)
                    {
                        // Deactivate the current room and activate the next room
                        // LevelManager->DeactivateAllRooms();
                        // LevelManager->ActivateRoomAt(NextRoom->GetRoomX(), NextRoom->GetRoomY());
                    }
                }
            }
        }
    }
}

// Called when another actor begins overlapping with this actor.
// Sets the interaction flag and logs the interactable actor.
void APlayerZDChar::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    if (OtherActor && (OtherActor->IsA(AHealthFountain::StaticClass()) ||
        OtherActor->IsA(AChest::StaticClass()) ||
        OtherActor->IsA(AMimic::StaticClass()) ||
        OtherActor->IsA(ADoor::StaticClass())))
    {
        bCanInteract = true;  // Allow interaction with the actor
        InteractableActor = OtherActor;  // Set the actor as interactable
        UE_LOG(LogTemp, Warning, TEXT("Interaction possible with: %s"), *OtherActor->GetName());
    }
}

// Called when another actor stops overlapping with this actor.
// Disables interaction and clears the interactable actor.
void APlayerZDChar::NotifyActorEndOverlap(AActor* OtherActor)
{
    Super::NotifyActorEndOverlap(OtherActor);

    if (OtherActor && OtherActor == InteractableActor)
    {
        bCanInteract = false;  // Disable interaction with the actor
        InteractableActor = nullptr;  // Clear the reference to the interactable actor
        UE_LOG(LogTemp, Log, TEXT("Interaction ended with: %s"), *OtherActor->GetName());
    }
}

// Handles the reception of an item, updates potion counts if the item is a potion, and destroys the item after it's received.
// Logs the type of the received item and updates the player's inventory accordingly.
void APlayerZDChar::ReciveItem(AItem* Item)
{
    if (Item)
    {
        UE_LOG(LogTemp, Log, TEXT("Received Item: %s"), *Item->GetClass()->GetName());

        // Check if the item is an attack potion
        if (Item->IsA(AAttackPotion::StaticClass()))
        {
            AttackPotionCount++;  // Increment the attack potion count
            UE_LOG(LogTemp, Log, TEXT("Received an Attack Potion. Total: %d"), AttackPotionCount);
        }
        // Check if the item is a shield potion
        else if (Item->IsA(AShieldPotion::StaticClass()))
        {
            ShieldPotionCount++;  // Increment the shield potion count
            UE_LOG(LogTemp, Log, TEXT("Received a Shield Potion. Total: %d"), ShieldPotionCount);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Received an item of unknown type."));  // Log a warning for unknown item types
        }

        // Destroy the item after it has been received and processed
        Item->Destroy();
    }
}

// Retrieves the player's current room based on their location in the game world.
// Calculates the room coordinates from the player's position and retrieves the corresponding room from the LevelManager.
// Returns nullptr if no room is found.
ARoom* APlayerZDChar::GetCurrentRoom() const
{
    // Retrieve the player's current location in the game world
    FVector PlayerLocation = GetActorLocation();

    // Compute the room coordinates based on the player's location
    int32 PlayerX = FMath::RoundToInt(PlayerLocation.X / 1500.0f);
    int32 PlayerY = FMath::RoundToInt(PlayerLocation.Y / 1500.0f);

    // Find the LevelManager instance in the world
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("LM"), FoundActors);

    // Iterate through the found actors to locate the LevelManager
    for (AActor* Actor : FoundActors)
    {
        ALevelManager* LevelManager = Cast<ALevelManager>(Actor);
        if (LevelManager)
        {
            // Return the room located at the computed coordinates
            return LevelManager->GetRoomAt(PlayerX, PlayerY);
        }
    }

    // Return nullptr if the LevelManager or room is not found
    return nullptr;
}
