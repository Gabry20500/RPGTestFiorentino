// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "PlayerZDChar.generated.h"


UENUM(BlueprintType)
enum class FPlayerDirection : uint8
{
	Up,
	Down,
	Left,
	Right
};


UCLASS()
class RPGTEST_API APlayerZDChar : public APaperZDCharacter
{
	GENERATED_BODY()
	
public:
	APlayerZDChar();

	void ApplyDamage(int DamageAmount);

	void Interact();

	void NotifyActorBeginOverlap(AActor* OtherActor);

	void NotifyActorEndOverlap(AActor* OtherActor);

	void ReciveItem(class AItem* Item);

protected:

	void BeginPlay();

	void Tick(float DeltaTime);

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	FRotator GetRotation();
	void MoveForeward(float AxisValue);
	void MoveRight(float AxisValue);

	void Attack();


	int Damage;
	int Health;
	int Shield;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerMovement")
	bool isAttacking;

	UPaperZDAnimationComponent* AnimationComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerMovement")
	FPlayerDirection PlyRotation;
private:
	
	bool bCanInteract;

	AActor* InteractableActor;

};
