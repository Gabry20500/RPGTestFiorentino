// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/Chest.h"
#include "Player/PlayerZDChar.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
AChest::AChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsOpened = false;
}

// Called when the game starts or when spawned
void AChest::BeginPlay()
{
	Super::BeginPlay();
	
	FlipbookComponent = FindComponentByClass<UPaperFlipbookComponent>();

	if (FlipbookComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("FlipbookComponent non trovato nella Chest!"));
	}
}

void AChest::ChangeFlipbook()
{
	if (FlipbookComponent && OpenedFlipbook && !bIsOpened)
	{
		FlipbookComponent->SetFlipbook(OpenedFlipbook);
		bIsOpened = true;
		UE_LOG(LogTemp, Log, TEXT("La chest è stata aperta."));
	}
}

void AChest::GiveItemToPlayer(APlayerZDChar* Player)
{
	if (bIsOpened && Player)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			// Select a random item
			TSubclassOf<AItem> SelectedItemClass = GetRandomItem();

			if (SelectedItemClass)
			{
				// Create the item and give it to the player
				AItem* Item = World->SpawnActor<AItem>(SelectedItemClass);
				if (Item)
				{
					// Call ReceiveItem on the player to handle adding the item to their inventory
					Player->ReciveItem(Item);
					UE_LOG(LogTemp, Log, TEXT("Player received: %s"), *Item->GetItemName());
				}
			}
		}
	}
}

TSubclassOf<AItem> AChest::GetRandomItem()
{
	if (ItemPool.Num() > 0)
	{
		// Seleziona un indice casuale dall'array di oggetti
		int32 RandomIndex = UKismetMathLibrary::RandomIntegerInRange(0, ItemPool.Num() - 1);
		return ItemPool[RandomIndex];
	}

	// Se non ci sono oggetti nella pool, restituisci nullptr
	return nullptr;
}

