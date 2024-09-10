// Fill out your copyright notice in the Description page of Project Settings.


#include "Minimap/Minimap.h"
#include "Components/UniformGridPanel.h"
#include "Engine/Texture2D.h"
#include "RoomGeneration/Room.h"



void UMinimap::UpdateMinimap(const TMap<FIntPoint, ERoomType>& RoomData)
{
    for (const TPair<FIntPoint, ERoomType>& RoomEntry : RoomData)
    {
        FIntPoint RoomKey = RoomEntry.Key;
        ERoomType RoomType = RoomEntry.Value;

        if (RoomImages.Contains(RoomKey))
        {
            UImage* RoomImage = *RoomImages.Find(RoomKey);

            // Update the image based on the room type
            if (RoomImage)
            {
                switch (RoomType)
                {
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
                    RoomImage->SetBrushFromTexture(UnexploredRoomIcon);
                    break;
                }
            }
        }
    }
}

void UMinimap::InitializeMinimap(int32 GridWidth, int32 GridHeight)
{
    if (MinimapGrid)
    {
        MinimapGrid->ClearChildren();
        RoomImages.Empty();

        // Create the grid dynamically
        for (int32 X = 0; X < GridWidth; ++X)
        {
            for (int32 Y = 0; Y < GridHeight; ++Y)
            {
                // Create a new image for each room
                UImage* RoomImage = NewObject<UImage>(this);
                RoomImage->SetBrushFromTexture(UnexploredRoomIcon);
                RoomImage->SetVisibility(ESlateVisibility::Visible);

                // Add the image to the grid at the corresponding location
                MinimapGrid->AddChildToUniformGrid(RoomImage, Y, X);

                // Save the reference in the map
                RoomImages.Add(FIntPoint(X, Y), RoomImage);
            }
        }
    }
}

void UMinimap::InitializeRoomIcons()
{
}
