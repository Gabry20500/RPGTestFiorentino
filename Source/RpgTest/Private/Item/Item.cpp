// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Item.h"

// Sets default values for this actor's properties
AItem::AItem()
{
    // Enable ticking for this actor, allowing it to call Tick() every frame.
    // This can be disabled if frame-by-frame updates are not needed for performance optimization.
    PrimaryActorTick.bCanEverTick = true;

    // Initialize the default item name
    ItemName = TEXT("Default Item");
}

// Called when the game starts or when the actor is spawned
void AItem::BeginPlay()
{
    Super::BeginPlay();
    // Additional initialization logic can be added here if needed
}

// Retrieves the name of the item
FString AItem::GetItemName() const
{
    return ItemName;
}

