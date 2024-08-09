// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/Chest.h"
#include "Player/PlayerZDChar.h"

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
	if (bIsOpened && ContainedItemClass && Player)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			// Creare l'oggetto e assegnarlo al player
			AItem* Item = World->SpawnActor<AItem>(ContainedItemClass);
			if (Item)
			{
				// Logica per aggiungere l'oggetto all'inventario del player
				// Qui dovresti aggiungere la funzione del player per ricevere l'oggetto
				//Player->ReciveItem(Item);
				UE_LOG(LogTemp, Log, TEXT("Il giocatore ha ricevuto: %s"), *Item->GetItemName());
			}
		}
	}
}

