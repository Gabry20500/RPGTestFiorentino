// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/HealthFountain.h"
#include <Components/BoxComponent.h>
#include <Player/PlayerZDChar.h>

// Sets default values
AHealthFountain::AHealthFountain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealAmount = 25.f;
	IsUsed = false;
}

// Called when the game starts or when spawned
void AHealthFountain::BeginPlay()
{
	Super::BeginPlay();
	FlipbookComponent = GetComponentByClass<UPaperFlipbookComponent>();
}

// Called every frame
void AHealthFountain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHealthFountain::HealPlayer(APlayerZDChar* PlayerCharacter)
{
	if (IsUsed == false) {
		if (PlayerCharacter)
		{
			PlayerCharacter->ApplyDamage(-HealAmount); // Curare il giocatore
			ChangeFlipbook();
		}
	}
}

void AHealthFountain::ChangeFlipbook()
{
	if (FlipbookComponent && UsedFlipbook)
	{
		FlipbookComponent->SetFlipbook(UsedFlipbook);
		IsUsed = true;
	}
}

