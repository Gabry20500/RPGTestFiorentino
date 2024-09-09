// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "ConsumableItem.generated.h"

/**
 * 
 */
UCLASS()
class RPGTEST_API AConsumableItem : public AItem
{
	GENERATED_BODY()

public:
	// Funzione per utilizzare l'oggetto (es. una pozione)
	UFUNCTION(BlueprintCallable, Category = "Item")
	virtual void UseItem(class APlayerZDChar* Player);

protected:
	// Definisce di quanto questo oggetto influisce su una statistica (es. punti vita, attacco, ecc.)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float EffectAmount;
	
};
