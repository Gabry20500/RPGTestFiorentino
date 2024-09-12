// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ConsumableItem.h"
#include "Player/PlayerZDChar.h"

// Implementation of UseItem for AConsumableItem
void AConsumableItem::UseItem(APlayerZDChar* Player)
{
    // Log message indicating that a consumable item has been used
    UE_LOG(LogTemp, Log, TEXT("Consumable used; performs an action."));
}
