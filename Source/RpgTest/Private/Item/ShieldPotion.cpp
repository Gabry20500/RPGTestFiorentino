// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ShieldPotion.h"
#include "Player/PlayerZDChar.h"

AShieldPotion::AShieldPotion()
{
	EffectAmount = 50.0f;
	ItemName = TEXT("Pozione di Shield");
}

void AShieldPotion::UseItem(APlayerZDChar* Player)
{
	if (Player)
	{
		// Aggiunge shield al player (qui dovresti implementare la logica per aumentare il valore del "shield" del player)
		Player->IncreaseShield(EffectAmount);

		UE_LOG(LogTemp, Log, TEXT("Il giocatore ha usato una pozione di shield."));
	}
}
