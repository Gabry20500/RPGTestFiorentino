// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player/PlayerZDChar.h"
#include "PaperFlipbookComponent.h"
#include "HealthFountain.generated.h"

UCLASS()
class RPGTEST_API AHealthFountain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthFountain();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HealPlayer(APlayerZDChar* PlayerCharacter);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Healing")
	float HealAmount;

	void ChangeFlipbook();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* FlipbookComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fountain", meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* UsedFlipbook;

	bool IsUsed;
};
