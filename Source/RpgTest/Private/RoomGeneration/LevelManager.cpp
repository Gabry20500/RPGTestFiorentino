// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomGeneration/LevelManager.h"
#include "Interactable/HealthFountain.h"
#include "Interactable/Chest.h"
#include "Interactable/Mimic.h"
#include "Enemy/GhostEnemy.h"
#include "Enemy/RatEnemy.h"
#include "Enemy/SlimeEnemy.h"
#include "Blueprint/UserWidget.h"
#include "Minimap/Minimap.h"
#include <Kismet/GameplayStatics.h>


// Sets default values
ALevelManager::ALevelManager()
{
    // Enable ticking to allow real-time updates if necessary
    PrimaryActorTick.bCanEverTick = true;
    PlayerX = 0; // Initialize player X position
    PlayerY = 0; // Initialize player Y position
}

// Called when the game starts or when spawned
void ALevelManager::BeginPlay()
{
    Super::BeginPlay();

    // Initialize the level grid and clear any previous level data
    InitializeLevelGrid();

    // Spawn rooms in the grid based on GridWidth and GridHeight
    for (int32 X = 0; X < GridWidth; ++X)
    {
        for (int32 Y = 0; Y < GridHeight; ++Y)
        {
            SpawnRoom(X, Y);
        }
    }

    // Initialize door connections between rooms
    InitializeDoors();

    // Mark the initial room as explored
    if (ARoom* InitialRoom = GetRoomAt(PlayerX, PlayerY))
    {
        InitialRoom->MarkAsExplored();
    }

    // Initialize the minimap widget
    if (MinimapWidgetClass)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            MinimapWidget = CreateWidget<UMinimap>(World, MinimapWidgetClass);
            if (MinimapWidget)
            {
                MinimapWidget->AddToViewport();
                MinimapWidget->SetVisibility(ESlateVisibility::Hidden); // Start hidden

                MinimapWidget->InitializeMinimap(GridHeight, GridWidth);
            }
        }
    }
}

void ALevelManager::InitializeLevelGrid()
{
    // Clear the level grid to ensure it starts empty
    LevelGrid.Empty();
}

void ALevelManager::MovePlayer(int32 DeltaX, int32 DeltaY)
{
    // Update player position with clamping to ensure it stays within bounds
    PlayerX = FMath::Clamp(DeltaX, 0, GridWidth - 1);
    PlayerY = FMath::Clamp(DeltaY, 0, GridHeight - 1);

    // Log the new player position for debugging purposes
    UE_LOG(LogTemp, Log, TEXT("Player Position: X=%d, Y=%d"), PlayerX, PlayerY);

    // Handle logic for when the player moves, including marking the room as explored
    if (ARoom* CurrentRoom = GetRoomAt(PlayerX, PlayerY))
    {
        if (!CurrentRoom->IsExplored())
        {
            CurrentRoom->MarkAsExplored();
        }

        // Update the minimap with current room data
        if (MinimapWidget)
        {
            TMap<FIntPoint, ARoom*> RoomData = GetRoomDataForMinimap();
            MinimapWidget->UpdateMinimap(RoomData);
        }
    }
}

void ALevelManager::InitializeDoors()
{
    // Iterate through all rooms and link doors to adjacent rooms
    for (auto& RoomEntry : LevelGrid)
    {
        ARoom* CurrentRoom = RoomEntry.Value;
        if (CurrentRoom)
        {
            // Get adjacent rooms
            ARoom* NorthRoom = GetRoomAt(CurrentRoom->RoomX + 1, CurrentRoom->RoomY);
            ARoom* SouthRoom = GetRoomAt(CurrentRoom->RoomX - 1, CurrentRoom->RoomY);
            ARoom* EastRoom = GetRoomAt(CurrentRoom->RoomX, CurrentRoom->RoomY + 1);
            ARoom* WestRoom = GetRoomAt(CurrentRoom->RoomX, CurrentRoom->RoomY - 1);

            // Link the doors
            CurrentRoom->LinkDoors(NorthRoom, SouthRoom, EastRoom, WestRoom);
        }
    }
}

void ALevelManager::SpawnRoom(int32 RoomX, int32 RoomY)
{
    int32 RandomValue = FMath::RandRange(0, 4);
    ERoomType RoomType;

    // Determine room type based on random value
    switch (RandomValue)
    {
    case 0:
        RoomType = ERoomType::Empty;
        break;
    case 1:
        RoomType = ERoomType::HealingFountain;
        break;
    case 2:
        RoomType = ERoomType::Chest;
        break;
    case 3:
        RoomType = ERoomType::Mimic;
        break;
    case 4:
        RoomType = ERoomType::Enemy;
        break;
    default:
        RoomType = ERoomType::Empty;
        break;
    }

    if (RoomBlueprint)
    {
        FVector SpawnLocation = FVector(RoomX * 1500.0f, RoomY * 1500.0f, 0.0f); // Calculate position
        ARoom* SpawnedRoom = GetWorld()->SpawnActor<ARoom>(RoomBlueprint, SpawnLocation, FRotator::ZeroRotator);

        if (SpawnedRoom)
        {
            SpawnedRoom->RoomX = RoomX;
            SpawnedRoom->RoomY = RoomY;
            SpawnedRoom->RoomType = RoomType;
            SpawnedRoom->SetRoomContent(0); // Set room content (ID or logic)

            LevelGrid.Add(FIntPoint(RoomX, RoomY), SpawnedRoom);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("RoomBlueprint is not assigned!"));
    }
}

void ALevelManager::SpawnAllRooms()
{
    // Spawn rooms at every position in the grid
    for (int32 X = 0; X < GridWidth; ++X)
    {
        for (int32 Y = 0; Y < GridHeight; ++Y)
        {
            SpawnRoom(X, Y);
        }
    }
}

TMap<FIntPoint, ARoom*> ALevelManager::GetRoomDataForMinimap() const
{
    TMap<FIntPoint, ARoom*> RoomData;

    // Add all rooms to the minimap data
    for (const auto& RoomEntry : LevelGrid)
    {
        const FIntPoint& RoomKey = RoomEntry.Key;
        ARoom* Room = RoomEntry.Value;

        if (Room)
        {
            RoomData.Add(RoomKey, Room);
        }
    }

    return RoomData;
}

void ALevelManager::ToggleMinimap(bool bShow)
{
    if (MinimapWidget)
    {
        if (bShow)
        {
            // Show the minimap and update it
            MinimapWidget->SetVisibility(ESlateVisibility::Visible);
            TMap<FIntPoint, ARoom*> RoomData = GetRoomDataForMinimap();
            MinimapWidget->UpdateMinimap(RoomData);
        }
        else
        {
            // Hide the minimap
            MinimapWidget->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}

void ALevelManager::ActivateRoomAt(int32 X, int32 Y)
{
    if (ARoom* Room = GetRoomAt(X, Y))
    {
        Room->ActivateRoom();
    }
}

void ALevelManager::DeactivateAllRooms()
{
    for (auto& RoomEntry : LevelGrid)
    {
        ARoom* Room = RoomEntry.Value;
        if (Room)
        {
            Room->DeactivateRoom();
        }
    }
}



ARoom* ALevelManager::GetRoomAt(int32 X, int32 Y) const
{
    // Create a key FIntPoint with X and Y
    FIntPoint RoomKey(X, Y);

    // Check if the map contains this key
    if (LevelGrid.Contains(RoomKey))
    {
        // If the key exists, return the pointer to the room
        return LevelGrid[RoomKey];
    }

    // If the key does not exist, return nullptr
    return nullptr;
}