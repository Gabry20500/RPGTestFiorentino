// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomGeneration/LevelManager.h"
#include "Interactable/HealthFountain.h"
#include "Interactable/Chest.h"
#include "Interactable/Mimic.h"
#include "Enemy/GhostEnemy.h"
#include "Enemy/RatEnemy.h"
#include "Enemy/SlimeEnemy.h"

// Sets default values
ALevelManager::ALevelManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    PlayerX = 0;
    PlayerY = 0;
}

// Called when the game starts or when spawned
void ALevelManager::BeginPlay()
{
	Super::BeginPlay();
    InitializeLevelGrid();
    LoadRoom(PlayerX, PlayerY);
    PreloadNearbyRooms(PlayerX, PlayerY);
}

void ALevelManager::InitializeLevelGrid()
{
    LevelGrid.SetNum(GridWidth);
    for (auto& Row : LevelGrid)
    {
        Row.SetNum(GridHeight);
        for (auto& Cell : Row)
        {
            Cell = nullptr; 
        }
    }
}

void ALevelManager::MovePlayer(int32 DeltaX, int32 DeltaY)
{
    int32 NewX = PlayerX + DeltaX;
    int32 NewY = PlayerY + DeltaY;

    if (LevelGrid.IsValidIndex(NewX) && LevelGrid[NewX].IsValidIndex(NewY))
    {
        PlayerX = NewX;
        PlayerY = NewY;
        LoadRoom(PlayerX, PlayerY);
        PreloadNearbyRooms(PlayerX, PlayerY);
    }
}

void ALevelManager::LoadRoom(int32 X, int32 Y)
{
    if (!LevelGrid.IsValidIndex(X) || !LevelGrid[X].IsValidIndex(Y))
        return;

    if (LevelGrid[X][Y] == nullptr) // Se la stanza non è già stata spawnata
    {
        if (RoomBlueprint == nullptr)
        {
            UE_LOG(LogTemp, Error, TEXT("RoomBlueprint is not assigned!"));
            return;
        }

        ERoomType RoomType = ERoomType::EnemyRoom; // Imposta un tipo di stanza predefinito
        SpawnRoom(X, Y, RoomType);
    }
}

void ALevelManager::PreloadNearbyRooms(int32 CenterX, int32 CenterY)
{
    const int32 Radius = 1; // Raggio di stanze da precaricare
    for (int32 X = CenterX - Radius; X <= CenterX + Radius; ++X)
    {
        for (int32 Y = CenterY - Radius; Y <= CenterY + Radius; ++Y)
        {
            if (LevelGrid.IsValidIndex(X) && LevelGrid[X].IsValidIndex(Y) && LevelGrid[X][Y] == nullptr)
            {
                ERoomType RoomType = ERoomType::EnemyRoom; // Imposta un tipo di stanza predefinito
                SpawnRoom(X, Y, RoomType);
            }
        }
    }
}


void ALevelManager::SpawnRoom(int32 RoomX, int32 RoomY, ERoomType RoomType)
{
    if (RoomBlueprint)
    {
        FVector SpawnLocation = FVector(RoomX * 1500.0f, RoomY * 1500.0f, 0.0f); // Calcola la posizione
        ARoom* SpawnedRoom = GetWorld()->SpawnActor<ARoom>(RoomBlueprint, SpawnLocation, FRotator::ZeroRotator);

        if (SpawnedRoom)
        {
            SpawnedRoom->RoomType = RoomType;
            SpawnedRoom->SetRoomContent(0); // Configura il contenuto della stanza (ID o logica)

            switch (RoomType)
            {
            case ERoomType::HealingFountain:
                if (GetWorld())
                {
                    GetWorld()->SpawnActor<AHealthFountain>(AHealthFountain::StaticClass(), SpawnLocation, FRotator::ZeroRotator);
                }
                break;

            case ERoomType::Chest:
                if (GetWorld())
                {
                    GetWorld()->SpawnActor<AChest>(AChest::StaticClass(), SpawnLocation, FRotator::ZeroRotator);
                }
                break;

            case ERoomType::Mimic:
                if (GetWorld())
                {
                    GetWorld()->SpawnActor<AMimic>(AMimic::StaticClass(), SpawnLocation, FRotator::ZeroRotator);
                }
                break;

            case ERoomType::EnemyRoom:
            {
                if (GetWorld())
                {
                    TArray<TSubclassOf<AEnemy>> Enemies;
                    Enemies.Add(AGhostEnemy::StaticClass());
                    Enemies.Add(ARatEnemy::StaticClass());
                    Enemies.Add(ASlimeEnemy::StaticClass());

                    if (Enemies.Num() > 0)
                    {
                        int32 RandomIndex = FMath::RandRange(0, Enemies.Num() - 1);
                        TSubclassOf<AEnemy> SelectedEnemy = Enemies[RandomIndex];
                        GetWorld()->SpawnActor<AEnemy>(SelectedEnemy, SpawnLocation, FRotator::ZeroRotator);
                    }
                }
            }
            break;

            default:
                break;
            }

            LevelGrid[RoomX][RoomY] = SpawnedRoom;
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("RoomBlueprint is not assigned!"));
    }
}

void ALevelManager::DestroyRoom(int32 RoomX, int32 RoomY)
{
    if (LevelGrid.IsValidIndex(RoomX) && LevelGrid[RoomX].IsValidIndex(RoomY) && LevelGrid[RoomX][RoomY])
    {
        LevelGrid[RoomX][RoomY]->Destroy();
        LevelGrid[RoomX][RoomY] = nullptr;
    }
}
