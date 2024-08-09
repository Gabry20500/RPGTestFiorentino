// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperFlipbookComponent.h"
#include <Item/Item.h>
#include "Chest.generated.h"

UCLASS()
class RPGTEST_API AChest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
    // Funzione per cambiare il flipbook della cassa quando viene aperta
    void ChangeFlipbook();

    // Funzione per dare un oggetto al player
    void GiveItemToPlayer(class APlayerZDChar* Player);

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UPaperFlipbookComponent* FlipbookComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chest", meta = (AllowPrivateAccess = "true"))
    UPaperFlipbook* OpenedFlipbook;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chest", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<AItem> ContainedItemClass;

    bool bIsOpened;
};
