// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

/**
 * AItem
 *
 * This class represents a base class for all items in the game. It extends from AActor and provides
 * fundamental properties and methods for items, such as an item name. This base class can be extended
 * to create various types of items with additional functionalities.
 */
UCLASS()
class RPGTEST_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Default constructor
	AItem();

protected:
	/**
	* BeginPlay
	*
	* Called when the game starts or when the actor is spawned. This method can be overridden to
	* include additional initialization logic.
	*/
	virtual void BeginPlay() override;

	/**
	 * ItemName
	 *
	 * The name of the item, exposed to both the editor and Blueprints. This property can be edited in
	 * the editor and accessed within Blueprints.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	FString ItemName;

public:

	/**
	 * GetItemName
	 *
	 * Retrieves the name of the item.
	 *
	 * @return The name of the item as a FString.
	 */
	UFUNCTION(BlueprintCallable, Category = "Item")
	FString GetItemName() const;

};
