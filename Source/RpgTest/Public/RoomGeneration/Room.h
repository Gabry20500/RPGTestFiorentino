// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Room.generated.h"

class ADoor;
class AHealthFountain;
class AChest;
class AEnemy;

UENUM(BlueprintType)
enum class ERoomType : uint8
{
    Empty UMETA(DisplayName = "Empty Room"),
    HealingFountain UMETA(DisplayName = "Healing Fountain Room"),
    Chest UMETA(DisplayName = "Chest Room"),
    Mimic UMETA(DisplayName = "Mimic Room"),
    Enemy UMETA(DisplayName = "Enemy Room")
};

UCLASS()
class RPGTEST_API ARoom : public AActor
{
	GENERATED_BODY()
	
public:
    // Sets default values for this actor's properties
    ARoom();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    /**
     * Sets the content of the room based on RoomID.
     * @param RoomID Unique identifier for the room's content.
     */
    void SetRoomContent(int32 RoomID);

    /** Marks the room as completed. */
    void MarkAsCompleted();

    /**
     * Links doors to adjacent rooms.
     * @param NorthRoom Room to the north.
     * @param SouthRoom Room to the south.
     * @param EastRoom Room to the east.
     * @param WestRoom Room to the west.
     */
    void LinkDoors(ARoom* NorthRoom, ARoom* SouthRoom, ARoom* EastRoom, ARoom* WestRoom);

    /** Activates the room and its doors. */
    void ActivateRoom();

    /** Deactivates the room and its doors. */
    void DeactivateRoom();

    /** Type of room. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Room", meta = (AllowPrivateAccess = "true"))
    ERoomType RoomType;
    
    /** Reference to the north door. */
    UPROPERTY()
    ADoor* NorthDoor;

    /** Reference to the south door. */
    UPROPERTY()
    ADoor* SouthDoor;

    /** Reference to the east door. */
    UPROPERTY()
    ADoor* EastDoor;

    /** Reference to the west door. */
    UPROPERTY()
    ADoor* WestDoor;

    UPROPERTY(BlueprintReadOnly, Category = "Room")
    int32 RoomX;

    UPROPERTY(BlueprintReadOnly, Category = "Room")
    int32 RoomY;

    // Getter per le coordinate della stanza
    int32 GetRoomX() const { return RoomX; }
    int32 GetRoomY() const { return RoomY; }

protected:
    /** Spawns room content based on room type. */
    void SpawnRoomContent();

private:

    /** Blueprints for enemies to spawn in enemy rooms. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Room", meta = (AllowPrivateAccess = "true"))
    TArray<TSubclassOf<AEnemy>> EnemyBlueprints;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Room", meta = (AllowPrivateAccess = "true"))
    TArray<TSubclassOf<AActor>> InteractBlueprints;

    /** Indicates if the room has been completed. */
    UPROPERTY(BlueprintReadOnly, Category = "Room", meta = (AllowPrivateAccess = "true"))
    bool bIsCompleted;

};
