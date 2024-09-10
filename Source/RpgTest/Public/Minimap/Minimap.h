// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Minimap.generated.h"

/**
 * 
 */
UCLASS()
class RPGTEST_API UMinimap : public UUserWidget
{
	GENERATED_BODY()
	
public:
    /** Updates the minimap with a new room */
    UFUNCTION(BlueprintCallable, Category = "Minimap")
    void UpdateMinimap(const TMap<FIntPoint, ERoomType>& RoomData);

    /** Sets the minimap grid size */
    UFUNCTION(BlueprintCallable, Category = "Minimap")
    void InitializeMinimap(int32 GridWidth, int32 GridHeight);

protected:
    /** Map containing the widget representations of rooms */
    UPROPERTY(BlueprintReadWrite, Category = "Minimap")
    TMap<FIntPoint, UImage*> RoomImages;

    /** Grid panel to hold the rooms' icons */
    UPROPERTY(meta = (BindWidget))
    class UUniformGridPanel* MinimapGrid;

    /** Image for unexplored rooms */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minimap")
    UTexture2D* UnexploredRoomIcon;

    /** Images for different room types */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minimap")
    UTexture2D* HealingFountainIcon;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minimap")
    UTexture2D* ChestRoomIcon;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minimap")
    UTexture2D* MimicRoomIcon;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minimap")
    UTexture2D* EnemyRoomIcon;

    /** Initializes the grid UI with empty rooms */
    void InitializeRoomIcons();
};
