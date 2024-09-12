// Fill out your copyright notice in the Description page of Project Settings.


#include "Minimap/Minimap.h"
#include "Components/UniformGridPanel.h"
#include "Engine/Texture2D.h"
#include "RoomGeneration/Room.h"


// Updates the minimap with the provided room data
void UMinimap::UpdateMinimap(const TMap<FIntPoint, ARoom*>& RoomData)
{
    // Iterate through each room in the provided data
    for (const TPair<FIntPoint, ARoom*>& RoomPair : RoomData)
    {
        FIntPoint RoomCoordinates = RoomPair.Key;
        ARoom* Room = RoomPair.Value;

        // Find the image widget corresponding to the room's coordinates
        if (UImage** RoomImagePtr = RoomImages.Find(RoomCoordinates))
        {
            UImage* RoomImage = *RoomImagePtr;

            // Set the appropriate icon based on whether the room is explored
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
                // Use the generic icon for unexplored rooms
                RoomImage->SetBrushFromTexture(GenericRoomIcon);
            }
        }
    }
}

// Initializes the minimap grid with the specified dimensions
void UMinimap::InitializeMinimap(int32 GridWidth, int32 GridHeight)
{
    if (MinimapGrid)
    {
        // Clear any existing widgets from the grid panel
        MinimapGrid->ClearChildren();
        RoomImages.Empty();

        // Create the grid layout dynamically based on the specified dimensions
        for (int32 X = 0; X < GridWidth; ++X)
        {
            for (int32 Y = 0; Y < GridHeight; ++Y)
            {
                // Create a new image widget for each room in the grid
                UImage* RoomImage = NewObject<UImage>(this);

                // Set the initial icon to the generic room icon
                RoomImage->SetBrushFromTexture(GenericRoomIcon);
                RoomImage->SetVisibility(ESlateVisibility::Visible);

                // Add the image widget to the grid panel at the specified location
                MinimapGrid->AddChildToUniformGrid(RoomImage, Y, X);

                // Store a reference to the image widget for future updates
                RoomImages.Add(FIntPoint(X, Y), RoomImage);
            }
        }
    }
}
