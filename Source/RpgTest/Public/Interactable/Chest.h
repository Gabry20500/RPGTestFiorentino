// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperFlipbookComponent.h"
#include <Item/Item.h>
#include "Chest.generated.h"

/**
 * AChest: Represents a chest object in the game that can be opened to provide items to the player.
 * The chest features a visual flipbook animation and can deliver a random item from a predefined pool when opened.
 */
UCLASS()
class RPGTEST_API AChest : public AActor
{
	GENERATED_BODY()
	
public:
    // Constructor: Sets default values for this actor's properties
    AChest();

protected:
    // Called when the game starts or when the chest is spawned
    virtual void BeginPlay() override;

public:
    // Function to change the flipbook animation of the chest when it is opened
    void ChangeFlipbook();

    // Function to give a random item from the chest's pool to the player
    void GiveItemToPlayer(class APlayerZDChar* Player);

private:
    // Component that handles the flipbook animation for the chest
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UPaperFlipbookComponent* FlipbookComponent;

    // Flipbook animation to display when the chest is opened
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chest", meta = (AllowPrivateAccess = "true"))
    UPaperFlipbook* OpenedFlipbook;

    // Pool of items that the chest can provide when opened
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chest", meta = (AllowPrivateAccess = "true"))
    TArray<TSubclassOf<AItem>> ItemPool;

    // Indicates whether the chest has been opened
    bool bIsOpened;

    // Retrieves a random item from the chest's item pool
    TSubclassOf<AItem> GetRandomItem();
};
