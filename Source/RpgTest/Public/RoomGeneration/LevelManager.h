// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Room.h"
#include "Door.h"
#include "LevelManager.generated.h"

/**
 * ALevelManager is responsible for managing the grid of rooms in the game level,
 * handling player movement between rooms, and managing the minimap display.
 */
UCLASS()
class RPGTEST_API ALevelManager : public AActor
{
	GENERATED_BODY()
	
public:

    // Sets default values for this actor's properties
    ALevelManager();

protected:

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:

    /**
     * Moves the player by a given delta in the grid.
     * @param DeltaX Change in X position.
     * @param DeltaY Change in Y position.
     */
    void MovePlayer(int32 DeltaX, int32 DeltaY);

    /**
    * Initializes all doors in the level.
    */
    void InitializeDoors();

    /** Blueprint class for the rooms */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level")
    TSubclassOf<ARoom> RoomBlueprint;

    /**
     * Gets the room at the specified grid location.
     * @param X X coordinate in the grid.
     * @param Y Y coordinate in the grid.
     * @return The room at the specified location.
     */
    ARoom* GetRoomAt(int32 X, int32 Y) const;

    /**
     * Activates the room at the specified grid location.
     * @param X X coordinate in the grid.
     * @param Y Y coordinate in the grid.
     */
    void ActivateRoomAt(int32 X, int32 Y);

    /**
     * Deactivates all rooms in the level.
     */
    void DeactivateAllRooms();

    /**
     * Gets the data for the minimap, including visited rooms.
     * @return A map of room locations to room instances for the minimap.
     */
    TMap<FIntPoint, ARoom*> GetRoomDataForMinimap() const;

    /**
     * Toggles the visibility of the minimap.
     * @param bShow Whether to show or hide the minimap.
     */
    void ToggleMinimap(bool bShow);

    /** Blueprint class for the minimap widget */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minimap")
    TSubclassOf<class UMinimap> MinimapWidgetClass;

    /** Instance of the minimap widget */
    UMinimap* MinimapWidget;

private:

    /** Initializes the grid of rooms for the level. */
    void InitializeLevelGrid();

    /** Spawns a room at the given grid location.
     * @param RoomX X coordinate in the grid.
     * @param RoomY Y coordinate in the grid.
     */
    void SpawnRoom(int32 RoomX, int32 RoomY);

    /** Spawns all rooms in the level. */
    void SpawnAllRooms();

    /** Grid configuration and player position */
    const int32 GridWidth = 15; // Width of the grid in rooms
    const int32 GridHeight = 21; // Height of the grid in rooms
    int32 PlayerX; // Current X position of the player
    int32 PlayerY; // Current Y position of the player

    /** Set of visited rooms to track which rooms have been encountered */
    TSet<FIntPoint> VisitedRooms;

    /** Map of grid locations to room instances */
    TMap<FIntPoint, ARoom*> LevelGrid;

};
