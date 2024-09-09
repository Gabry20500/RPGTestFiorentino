// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ConsumableItem.h"
#include "ShieldPotion.generated.h"

/**
 * 
 */
UCLASS()
class RPGTEST_API AShieldPotion : public AConsumableItem
{
	GENERATED_BODY()
	
public:
	AShieldPotion();

	virtual void UseItem(class APlayerZDChar* Player) override;
};
