// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomGeneration/Room.h"
#include "Engine/World.h"
#include "Interactable/HealthFountain.h"
#include "Interactable/Chest.h"
#include "Interactable/Mimic.h"
#include "Enemy/Enemy.h"
#include "RoomGeneration/Door.h"
#include "RoomGeneration/LevelManager.h"
#include "Components/ChildActorComponent.h"
#include "Components/ActorComponent.h"
#include <Minimap/Minimap.h>
#include <Kismet/GameplayStatics.h>

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
	
    // Iterate through all components attached to this actor
    TArray<UActorComponent*> Components;
    GetComponents(Components);

    for (UActorComponent* Component : Components)
    {
        UChildActorComponent* ChildActorComponent = Cast<UChildActorComponent>(Component);
        if (ChildActorComponent)
        {
            // Check for the NorthDoor tag
            if (ChildActorComponent->ComponentHasTag(FName("NorthDoor")))
            {
                NorthDoor = Cast<ADoor>(ChildActorComponent->GetChildActor());
            }
            // Check for the SouthDoor tag
            else if (ChildActorComponent->ComponentHasTag(FName("SouthDoor")))
            {
                SouthDoor = Cast<ADoor>(ChildActorComponent->GetChildActor());
            }
            // Check for the EastDoor tag
            else if (ChildActorComponent->ComponentHasTag(FName("EastDoor")))
            {
                EastDoor = Cast<ADoor>(ChildActorComponent->GetChildActor());
            }
            // Check for the WestDoor tag
            else if (ChildActorComponent->ComponentHasTag(FName("WestDoor")))
            {
                WestDoor = Cast<ADoor>(ChildActorComponent->GetChildActor());
            }
        }
    }
}

void ARoom::SetRoomContent(int32 RoomID)
{
    if (!bIsCompleted)
    {
        SpawnRoomContent();
    }
}

void ARoom::MarkAsCompleted()
{
    bIsCompleted = true;
}

void ARoom::LinkDoors(ARoom* NorthRoom, ARoom* SouthRoom, ARoom* EastRoom, ARoom* WestRoom)
{
    // Link North Door
    if (NorthDoor && NorthRoom)
    {
        NorthDoor->LinkToRoom(NorthRoom);
        NorthDoor->SetActorHiddenInGame(false);
        NorthDoor->SetActorEnableCollision(true);
    }

    // Link South Door
    if (SouthDoor && SouthRoom)
    {
        SouthDoor->LinkToRoom(SouthRoom);
        SouthDoor->SetActorHiddenInGame(false);
        SouthDoor->SetActorEnableCollision(true);
    }

    // Link East Door
    if (EastDoor && EastRoom)
    {
        EastDoor->LinkToRoom(EastRoom);
        EastDoor->SetActorHiddenInGame(false);
        EastDoor->SetActorEnableCollision(true);
    }

    // Link West Door
    if (WestDoor && WestRoom)
    {
        WestDoor->LinkToRoom(WestRoom);
        WestDoor->SetActorHiddenInGame(false);
        WestDoor->SetActorEnableCollision(true);
    }
}

void ARoom::ActivateRoom()
{
    SetActorHiddenInGame(false);
    SetActorEnableCollision(true);

    if (NorthDoor)
    {
        NorthDoor->SetActorHiddenInGame(false);
        NorthDoor->SetActorEnableCollision(true);
    }
    if (SouthDoor)
    {
        SouthDoor->SetActorHiddenInGame(false);
        SouthDoor->SetActorEnableCollision(true);
    }
    if (EastDoor)
    {
        EastDoor->SetActorHiddenInGame(false);
        EastDoor->SetActorEnableCollision(true);
    }
    if (WestDoor)
    {
        WestDoor->SetActorHiddenInGame(false);
        WestDoor->SetActorEnableCollision(true);
    }
}

void ARoom::DeactivateRoom()
{
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);

    if (NorthDoor)
    {
        NorthDoor->SetActorHiddenInGame(true);
        NorthDoor->SetActorEnableCollision(false);
    }
    if (SouthDoor)
    {
        SouthDoor->SetActorHiddenInGame(true);
        SouthDoor->SetActorEnableCollision(false);
    }
    if (EastDoor)
    {
        EastDoor->SetActorHiddenInGame(true);
        EastDoor->SetActorEnableCollision(false);
    }
    if (WestDoor)
    {
        WestDoor->SetActorHiddenInGame(true);
        WestDoor->SetActorEnableCollision(false);
    }
}

void ARoom::MarkAsExplored()
{
    bIsExplored = true;

    ALevelManager* LMInstance = Cast<ALevelManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ALevelManager::StaticClass()));
    UMinimap* Minimap = LMInstance->MinimapWidget;
    if (Minimap)
    {
        TMap<FIntPoint, ARoom*> RoomData;
        RoomData.Add(FIntPoint(RoomX, RoomY), this);
        Minimap->UpdateMinimap(RoomData);
    }
}

void ARoom::SpawnRoomContent()
{
    switch (RoomType)
    {
    case ERoomType::HealingFountain:
        GetWorld()->SpawnActor<AHealthFountain>(InteractBlueprints[0], GetActorLocation() + FVector(15.f, 40.f, 127.f), FRotator::ZeroRotator);
        break;

    case ERoomType::Chest:
        GetWorld()->SpawnActor<AChest>(InteractBlueprints[1], GetActorLocation() + FVector(15.f, 40.f, 50.f), FRotator::ZeroRotator);
        break;

    case ERoomType::Mimic:
        GetWorld()->SpawnActor<AMimic>(InteractBlueprints[2], GetActorLocation() + FVector(15.f, 40.f, 300.f), FRotator::ZeroRotator);
        break;

    case ERoomType::Enemy:
        if (EnemyBlueprints.Num() > 0)
        {
            // Pick a random enemy from the array
            int32 RandomIndex = FMath::RandRange(0, EnemyBlueprints.Num() - 1);
            TSubclassOf<AEnemy> SelectedEnemyBlueprint = EnemyBlueprints[RandomIndex];

            // Spawn the selected enemy
            if (SelectedEnemyBlueprint)
            {
                GetWorld()->SpawnActor<AEnemy>(SelectedEnemyBlueprint, GetActorLocation() + FVector(15.f, 40.f,15.f), FRotator::ZeroRotator);
            }
        }
        break;

    default:
        break;
    }
}
