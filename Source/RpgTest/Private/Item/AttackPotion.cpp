// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/AttackPotion.h"
#include "Player/PlayerZDChar.h"

// Constructor: Initializes default values for the attack potion
AAttackPotion::AAttackPotion()
{
	// Set the amount of attack effect the potion provides
	EffectAmount = 20.0f;

	// Set the display name of the item
	ItemName = TEXT("Attack Potion");
}

// Override of the UseItem function from AConsumableItem
void AAttackPotion::UseItem(APlayerZDChar* Player)
{
    if (Player)
    {
        // Apply the attack boost effect to the player
        Player->IncreaseAttack(EffectAmount);

        // Log a message indicating that the potion has been used
        UE_LOG(LogTemp, Log, TEXT("The player has used an attack potion."));
    }
}
