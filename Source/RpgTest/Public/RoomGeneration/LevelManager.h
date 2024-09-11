// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Room.h"
#include "Door.h"
#include "LevelManager.generated.h"

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

    void InitializeDoors();
    /** Blueprint for the rooms */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level")
    TSubclassOf<ARoom> RoomBlueprint;

    /** Gets the room at the specified location. */
    ARoom* GetRoomAt(int32 X, int32 Y) const;

    void ActivateRoomAt(int32 X, int32 Y);

    void DeactivateAllRooms();

    TMap<FIntPoint, ARoom*> GetRoomDataForMinimap() const;

    void ToggleMinimap(bool bShow);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minimap")
    TSubclassOf<class UMinimap> MinimapWidgetClass; // Riferimento al Blueprint del widget
    
    UMinimap* MinimapWidget;
private:
    /** Initializes the level grid. */
    void InitializeLevelGrid();

    /** Spawns a room at the given location. */
    void SpawnRoom(int32 RoomX, int32 RoomY);

    void SpawnAllRooms();

    /** Grid configuration and player position */
    const int32 GridWidth = 15;
    const int32 GridHeight = 21;
    int32 PlayerX;
    int32 PlayerY;

    TSet<FIntPoint> VisitedRooms;


    /** Grid configuration and player position */
    TMap<FIntPoint, ARoom*> LevelGrid;

};
