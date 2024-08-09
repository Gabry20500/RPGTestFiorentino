// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Room.h"
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
    void MovePlayer(int32 DeltaX, int32 DeltaY);
    void LoadRoom(int32 X, int32 Y);
    void PreloadNearbyRooms(int32 CenterX, int32 CenterY);

    // Proprieta' di configurazione della stanza
    UPROPERTY(EditDefaultsOnly, Category = "Level")
    TSubclassOf<ARoom> RoomBlueprint; // Blueprint di base per le stanze

private:
    void InitializeLevelGrid();
    void SpawnRoom(int32 RoomX, int32 RoomY, ERoomType RoomType);
    void DestroyRoom(int32 RoomX, int32 RoomY);

    TArray<TArray<ARoom*>> LevelGrid;
    const int32 GridWidth = 21;
    const int32 GridHeight = 15;
    int32 PlayerX;
    int32 PlayerY;
};
