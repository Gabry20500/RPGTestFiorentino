// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/AttackPotion.h"
#include "Player/PlayerZDChar.h"

AAttackPotion::AAttackPotion()
{
	EffectAmount = 20.0f;
	ItemName = TEXT("Pozione di Attacco");
}

void AAttackPotion::UseItem(APlayerZDChar* Player)
{
	if (Player)
	{
		Player->IncreaseAttack(EffectAmount);

		UE_LOG(LogTemp, Log, TEXT("Il giocatore ha usato una pozione di attacco."));
	}
}
