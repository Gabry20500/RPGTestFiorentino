// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ConsumableItem.h"
#include "ShieldPotion.generated.h"

/**
 * AShieldPotion
 *
 * This class represents a type of consumable item that grants a shield boost when used. It inherits
 * from AConsumableItem, extending its functionality to support shield-specific effects.
 *
 * This class must override the UseItem method to define the specific behavior of applying the shield
 * potion effect to a player character.
 */
UCLASS()
class RPGTEST_API AShieldPotion : public AConsumableItem
{
	GENERATED_BODY()
	
public:

	// Default constructor
	AShieldPotion();

	/**
	* Override of the UseItem function from AConsumableItem.
	*
	* Applies the shield potion effect to the specified player character.
	*
	* @param Player The player character to apply the potion effect to.
	*/
	virtual void UseItem(class APlayerZDChar* Player) override;
};
