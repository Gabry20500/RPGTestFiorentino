// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomGeneration/Door.h"
#include "RoomGeneration/LevelManager.h"
#include "Engine/World.h"

// Sets default values
ADoor::ADoor()
{
    // Disable ticking if not necessary
    PrimaryActorTick.bCanEverTick = false;
    LinkedRoom = nullptr; // Initialize the linked room to nullptr
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
    Super::BeginPlay();
}

// Link the door to another room
void ADoor::LinkToRoom(ARoom* InLinkedRoom)
{
    if (InLinkedRoom != nullptr)
    {
        LinkedRoom = InLinkedRoom;
    }
}

ARoom* ADoor::GetLinkedRoom()
{
    return LinkedRoom;
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
