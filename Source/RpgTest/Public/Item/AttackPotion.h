// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ConsumableItem.h"
#include "AttackPotion.generated.h"

/**
 * 
 */
UCLASS()
class RPGTEST_API AAttackPotion : public AConsumableItem
{
	GENERATED_BODY()

public:
	AAttackPotion();

	virtual void UseItem(class APlayerZDChar* Player) override;
	
};
