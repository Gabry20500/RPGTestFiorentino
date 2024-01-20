// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class RPGTESTFIORENTINO_API APlayerCharacter : public APaperZDCharacter
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "Player")
	bool bIsRunning = false;
};
