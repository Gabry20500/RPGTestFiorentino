// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/HealthFountain.h"
#include <Components/BoxComponent.h>
#include <Player/PlayerZDChar.h>

// Sets default values
AHealthFountain::AHealthFountain()
{
	// Set this actor to call Tick() every frame. This can be turned off if performance needs to be improved.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize the amount of health to be restored and set the fountain to not yet used.
	HealAmount = 25.f;
	IsUsed = false;
}

// Called when the game starts or when spawned
void AHealthFountain::BeginPlay()
{
	Super::BeginPlay();

	// Find the PaperFlipbookComponent attached to this actor.
	FlipbookComponent = GetComponentByClass<UPaperFlipbookComponent>();
}

// Called every frame
void AHealthFountain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Currently, no per-frame updates are needed for the HealthFountain.
}

void AHealthFountain::HealPlayer(APlayerZDChar* PlayerCharacter)
{
	if (!IsUsed) // Check if the fountain has already been used.
	{
		if (PlayerCharacter)
		{
			// Heal the player by applying negative damage, which effectively increases their health.
			PlayerCharacter->ApplyDamage(-HealAmount);

			// Change the flipbook to show that the fountain has been used.
			ChangeFlipbook();
		}
	}
}

void AHealthFountain::ChangeFlipbook()
{
	if (FlipbookComponent && UsedFlipbook)
	{
		// Set the flipbook to the "used" animation.
		FlipbookComponent->SetFlipbook(UsedFlipbook);

		// Mark the fountain as used so it can't heal again.
		IsUsed = true;
	}
}

