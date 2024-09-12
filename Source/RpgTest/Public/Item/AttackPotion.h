// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ConsumableItem.h"
#include "AttackPotion.generated.h"

/**
 * AAttackPotion
 *
 * This class represents a type of consumable item that grants an attack boost when used.
 * It extends from AConsumableItem, inheriting its properties and behaviors.
 *
 * @note This class must override the UseItem method to define the specific behavior
 *       of applying the attack potion effect to a player character.
 */
UCLASS()
class RPGTEST_API AAttackPotion : public AConsumableItem
{
	GENERATED_BODY()

public:
	// Default constructor
	AAttackPotion();

	/**
	 * Override of the UseItem function from AConsumableItem.
	 *
	 * Applies the attack potion effect to the specified player character.
	 *
	 * @param Player The player character to apply the potion effect to.
	 */
	virtual void UseItem(class APlayerZDChar* Player) override;
	
};
