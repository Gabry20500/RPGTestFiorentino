// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomGeneration/Door.h"
#include "RoomGeneration/LevelManager.h"
#include "Engine/World.h"

// Sets default values
ADoor::ADoor()
{
    // Disable ticking as it's not required for this actor
    PrimaryActorTick.bCanEverTick = false;

    // Initialize the linked room to nullptr
    LinkedRoom = nullptr;
}

// Link the door to another room
void ADoor::LinkToRoom(ARoom* InLinkedRoom)
{
    // Check if the provided room is valid before linking
    if (InLinkedRoom != nullptr)
    {
        LinkedRoom = InLinkedRoom;
    }
}

// Get the room that this door is linked to
ARoom* ADoor::GetLinkedRoom()
{
    return LinkedRoom;
}
