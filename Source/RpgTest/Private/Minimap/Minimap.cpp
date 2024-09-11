// Fill out your copyright notice in the Description page of Project Settings.


#include "Minimap/Minimap.h"
#include "Components/UniformGridPanel.h"
#include "Engine/Texture2D.h"
#include "RoomGeneration/Room.h"



void UMinimap::UpdateMinimap(const TMap<FIntPoint, ARoom*>& RoomData)
{
    for (const TPair<FIntPoint, ARoom*>& RoomPair : RoomData)
    {
        FIntPoint RoomCoordinates = RoomPair.Key;
        ARoom* Room = RoomPair.Value;

        // Trova l'immagine della stanza basata sulle coordinate
        if (UImage** RoomImagePtr = RoomImages.Find(RoomCoordinates))
        {
            UImage* RoomImage = *RoomImagePtr;

            // Se la stanza è esplorata, usa l'icona corrispondente
            if (Room->IsExplored())
            {
                switch (Room->RoomType)
                {
                case ERoomType::Empty:
                    RoomImage->SetBrushFromTexture(EmptyRoomIcon);
                    break;

                case ERoomType::HealingFountain:
                    RoomImage->SetBrushFromTexture(HealingFountainIcon);
                    break;

                case ERoomType::Chest:
                    RoomImage->SetBrushFromTexture(ChestRoomIcon);
                    break;

                case ERoomType::Mimic:
                    RoomImage->SetBrushFromTexture(MimicRoomIcon);
                    break;

                case ERoomType::Enemy:
                    RoomImage->SetBrushFromTexture(EnemyRoomIcon);
                    break;

                default:
                    RoomImage->SetBrushFromTexture(EmptyRoomIcon);
                    break;
                }
            }
            else
            {
                // Se la stanza non è esplorata, usa l'icona generica
                RoomImage->SetBrushFromTexture(GenericRoomIcon);
            }
        }
    }
}

void UMinimap::InitializeMinimap(int32 GridWidth, int32 GridHeight)
{
    if (MinimapGrid)
    {
        // Clear any existing widgets in the grid
        MinimapGrid->ClearChildren();
        RoomImages.Empty();

        // Create the grid dynamically
        for (int32 X = 0; X < GridWidth; ++X)
        {
            for (int32 Y = 0; Y < GridHeight; ++Y)
            {
                // Create a new image for each room
                UImage* RoomImage = NewObject<UImage>(this);

                // Set the initial icon to be the unexplored room icon
                RoomImage->SetBrushFromTexture(GenericRoomIcon);
                RoomImage->SetVisibility(ESlateVisibility::Visible);

                // Add the image to the grid at the corresponding location
                MinimapGrid->AddChildToUniformGrid(RoomImage, Y, X);

                // Save the reference in the map for later updates
                RoomImages.Add(FIntPoint(X, Y), RoomImage);
            }
        }
    }
}

void UMinimap::InitializeRoomIcons()
{
}
