// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/Chest.h"
#include "Player/PlayerZDChar.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
AChest::AChest()
{
	// Enable ticking for this actor if required for dynamic behavior
	PrimaryActorTick.bCanEverTick = true;

	// Initialize the chest as closed
	bIsOpened = false;
}

// Called when the game starts or when spawned
void AChest::BeginPlay()
{
	Super::BeginPlay();

	// Find and assign the FlipbookComponent if it exists
	FlipbookComponent = FindComponentByClass<UPaperFlipbookComponent>();

	if (FlipbookComponent == nullptr)
	{
		// Log a warning if the FlipbookComponent is not found, which is crucial for chest animation
		UE_LOG(LogTemp, Warning, TEXT("FlipbookComponent not found in Chest!"));
	}
}

void AChest::ChangeFlipbook()
{
	// Ensure the chest has a flipbook component and the opened flipbook is set
	if (FlipbookComponent && OpenedFlipbook && !bIsOpened)
	{
		// Set the flipbook to the opened animation
		FlipbookComponent->SetFlipbook(OpenedFlipbook);

		// Mark the chest as opened
		bIsOpened = true;

		// Log that the chest has been opened
		UE_LOG(LogTemp, Log, TEXT("The chest has been opened."));
	}
}

void AChest::GiveItemToPlayer(APlayerZDChar* Player)
{
	// Ensure the chest is opened and the player is valid
	if (bIsOpened && Player)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			// Select a random item from the item pool
			TSubclassOf<AItem> SelectedItemClass = GetRandomItem();

			if (SelectedItemClass)
			{
				// Spawn the item in the world
				AItem* Item = World->SpawnActor<AItem>(SelectedItemClass);
				if (Item)
				{
					// Call ReceiveItem on the player to handle adding the item to their inventory
					Player->ReciveItem(Item);

					// Log the item that was given to the player
					UE_LOG(LogTemp, Log, TEXT("Player received: %s"), *Item->GetItemName());
				}
			}
		}
	}
}

TSubclassOf<AItem> AChest::GetRandomItem()
{
	// Ensure there are items in the pool before selecting one
	if (ItemPool.Num() > 0)
	{
		// Select a random index from the item pool array
		int32 RandomIndex = UKismetMathLibrary::RandomIntegerInRange(0, ItemPool.Num() - 1);
		return ItemPool[RandomIndex];
	}

	// Return nullptr if no items are available in the pool
	return nullptr;
}

