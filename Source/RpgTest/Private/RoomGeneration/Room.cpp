// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomGeneration/Room.h"
#include "Engine/World.h"
#include "Interactable/HealthFountain.h"
#include "Interactable/Chest.h"
#include "Interactable/Mimic.h"
#include "Enemy/GhostEnemy.h"
#include "Enemy/RatEnemy.h"
#include "Enemy/SlimeEnemy.h"

// Sets default values
ARoom::ARoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsCompleted = false;
}

// Called when the game starts or when spawned
void ARoom::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARoom::SetRoomContent(int32 RoomID)
{
    if (!bIsCompleted)
    {
        SpawnRoomContent();
    }
    else
    {
        // Logica per gestire una stanza già completata
        return;
    }
}

void ARoom::MarkAsCompleted()
{
    bIsCompleted = true;
}

void ARoom::SpawnRoomContent()
{
    switch (RoomType)
    {
    case ERoomType::HealingFountain:
        GetWorld()->SpawnActor<AHealthFountain>(AHealthFountain::StaticClass(), GetActorLocation(), FRotator::ZeroRotator);
        break;

    case ERoomType::Chest:
        GetWorld()->SpawnActor<AChest>(AChest::StaticClass(), GetActorLocation(), FRotator::ZeroRotator);
        break;

    case ERoomType::EnemyRoom:
        if (EnemyBlueprints.Num() > 0)
        {
            // Scegli un nemico casualmente dall'array
            int32 RandomIndex = FMath::RandRange(0, EnemyBlueprints.Num() - 1);
            TSubclassOf<AActor> SelectedEnemyBlueprint = EnemyBlueprints[RandomIndex];

            // Spawn del nemico selezionato
            GetWorld()->SpawnActor<AActor>(SelectedEnemyBlueprint, GetActorLocation(), FRotator::ZeroRotator);
        }
        break;

    default:
        break;
    }
}
