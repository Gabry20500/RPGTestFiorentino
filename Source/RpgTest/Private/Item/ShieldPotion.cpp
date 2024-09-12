// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ShieldPotion.h"
#include "Player/PlayerZDChar.h"

// Constructor: Initializes default values for the shield potion
AShieldPotion::AShieldPotion()
{
	// Set the amount of shield effect the potion provides
	EffectAmount = 50.0f;

	// Set the display name of the item
	ItemName = TEXT("Shield Potion");
}

// Override of the UseItem function from AConsumableItem
void AShieldPotion::UseItem(APlayerZDChar* Player)
{
    if (Player)
    {
        // Apply the shield boost effect to the player
        Player->IncreaseShield(EffectAmount);

        // Log a message indicating that the shield potion has been used
        UE_LOG(LogTemp, Log, TEXT("The player has used a shield potion."));
    }
}
