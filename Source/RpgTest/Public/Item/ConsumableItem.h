// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "ConsumableItem.generated.h"

/**
 * AConsumableItem
 *
 * This class represents a base class for consumable items that can affect a player character's attributes.
 * It extends from AItem, adding functionality specific to items that can be used by the player.
 *
 * Consumable items include potions, food, and other items that can provide effects such as healing
 * or stat boosts when used.
 */
UCLASS()
class RPGTEST_API AConsumableItem : public AItem
{
	GENERATED_BODY()

public:
    /**
    * UseItem
    *
    * This function applies the effect of the consumable item to the specified player character.
    * It must be overridden by subclasses to define specific behavior for different types of consumable items.
    *
    * @param Player The player character to apply the item's effect to.
    */
    UFUNCTION(BlueprintCallable, Category = "Item")
	virtual void UseItem(class APlayerZDChar* Player);

protected:
    /**
    * EffectAmount
    *
    * The amount by which the consumable item affects a statistic (e.g., health points, attack power, etc.).
    * This property can be edited in the editor and is exposed to Blueprint for further customization.
    */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float EffectAmount;
	
};
