// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class ARoom;

UCLASS()
class RPGTEST_API ADoor : public AActor
{
    GENERATED_BODY()
    
public:
    // Sets default values for this actor's properties
    ADoor();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    /**
     * Links this door to a specific room.
     * @param InLinkedRoom The room that this door leads to.
     */
    void LinkToRoom(ARoom* InLinkedRoom);

    ARoom* GetLinkedRoom();
protected:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    /** The room that this door leads to. */
    UPROPERTY()
    ARoom* LinkedRoom; // Room that this door leads to
};
