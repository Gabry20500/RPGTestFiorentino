// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class ARoom;

/**
 * ADoor represents a door in the game that can link to a specific room.
 */
UCLASS()
class RPGTEST_API ADoor : public AActor
{
    GENERATED_BODY()
    
public:
    // Sets default values for this actor's properties
    ADoor();

    /**
     * Links this door to a specific room.
     * @param InLinkedRoom The room that this door leads to.
     */
    void LinkToRoom(ARoom* InLinkedRoom);

    /**
     * Gets the room that this door is linked to.
     * @return The room that this door leads to.
     */
    ARoom* GetLinkedRoom();

private:
    /** The room that this door leads to. */
    UPROPERTY()
    ARoom* LinkedRoom; // Room that this door leads to
};
