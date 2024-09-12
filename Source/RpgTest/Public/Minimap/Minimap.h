// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Minimap.generated.h"

/**
 * UMinimap
 *
 * This class represents a minimap widget for displaying a visual representation of the game world.
 * It inherits from UUserWidget and provides functionality for updating and initializing the minimap,
 * as well as managing the icons representing different types of rooms.
 */
UCLASS()
class RPGTEST_API UMinimap : public UUserWidget
{
	GENERATED_BODY()
	
public:
    /**
     * Updates the minimap with a new room layout.
     *
     * @param RoomData A map containing the room data, where the key is the room's location and the value is the room actor.
     */
    UFUNCTION(BlueprintCallable, Category = "Minimap")
    void UpdateMinimap(const TMap<FIntPoint, ARoom*>& RoomData);

    /**
     * Sets the grid size for the minimap.
     *
     * @param GridWidth The width of the minimap grid.
     * @param GridHeight The height of the minimap grid.
     */
    UFUNCTION(BlueprintCallable, Category = "Minimap")
    void InitializeMinimap(int32 GridWidth, int32 GridHeight);

protected:
    /**
     * Map containing widget representations of rooms.
     *
     * This map associates room coordinates with their corresponding UI images.
     */
    UPROPERTY(BlueprintReadWrite, Category = "Minimap")
    TMap<FIntPoint, UImage*> RoomImages;

    /**
     * Grid panel to hold the room icons.
     *
     * This panel organizes the icons in a grid layout.
     */
    UPROPERTY(meta = (BindWidget))
    class UUniformGridPanel* MinimapGrid;

    /**
     * Image used for unexplored rooms.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minimap")
    UTexture2D* GenericRoomIcon;

    /**
     * Image used for empty rooms.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minimap")
    UTexture2D* EmptyRoomIcon;

    /**
     * Image used for healing fountain rooms.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minimap")
    UTexture2D* HealingFountainIcon;

    /**
     * Image used for chest rooms.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minimap")
    UTexture2D* ChestRoomIcon;

    /**
     * Image used for mimic rooms.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minimap")
    UTexture2D* MimicRoomIcon;

    /**
     * Image used for enemy rooms.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minimap")
    UTexture2D* EnemyRoomIcon;
};
