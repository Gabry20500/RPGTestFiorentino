// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Room.generated.h"

UENUM(BlueprintType)
enum class ERoomType : uint8
{
	HealingFountain,
	Chest,
	Mimic,
	EnemyRoom
};

UCLASS()
class RPGTEST_API ARoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void SetRoomContent(int32 RoomID);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Room")
	ERoomType RoomType;

	UPROPERTY(EditDefaultsOnly, Category = "Room")
	TArray<TSubclassOf<AActor>> EnemyBlueprints;

	UPROPERTY(BlueprintReadOnly, Category = "Room")
	bool bIsCompleted; // Stato della stanza

	void MarkAsCompleted(); // Funzione per marcare la stanza come completata

private:
	void SpawnRoomContent();

};
