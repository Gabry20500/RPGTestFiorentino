// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PlayerChar.generated.h"


UENUM(BlueprintType)
enum class FPlayerDirection : uint8
{
	None,
	Up,
	Down,
	Left,
	Right
};


/**
 * 
 */
UCLASS()
class RPGTEST_API APlayerChar : public APaperCharacter
{
	GENERATED_BODY()

public:
	APlayerChar();

protected:

	void BeginPlay();

	void Tick(float DeltaTime);

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	void MoveForeward(float AxisValue);
	void MoveRight(float AxisValue);

	void Attack();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerMovement")
	bool inMovement;

	UStaticMeshComponent* Body;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerMovement")
	FPlayerDirection PlyRotation;
	
};
