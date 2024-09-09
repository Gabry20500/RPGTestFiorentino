// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerZDChar.h"
#include "PaperZDAnimationComponent.h"
#include "PaperZDAnimInstance.h"
#include <Enemy/Enemy.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Interactable/HealthFountain.h>
#include <Interactable/Chest.h>
#include <Interactable/Mimic.h>
#include <RoomGeneration/Door.h>
#include <RoomGeneration/Room.h>
#include <RoomGeneration/LevelManager.h>
#include <Kismet/GameplayStatics.h>

APlayerZDChar::APlayerZDChar()
{
	PrimaryActorTick.bCanEverTick = true;

    Damage = 35;
    Health = 100;
    Shield = 0;

    bCanInteract = false;
    InteractableActor = nullptr;

    PlayerLevel = 1;
    CurrentXP = 0;
    XPToNextLevel = 100;
}

void APlayerZDChar::GainXP(int32 Amount)
{
    CurrentXP += Amount;

    UE_LOG(LogTemp, Log, TEXT("XP Gained: %d, Current XP: %d"), Amount, CurrentXP);

    if (CurrentXP >= XPToNextLevel)
    {
        CurrentXP -= XPToNextLevel;
        PlayerLevel++;
        XPToNextLevel += 50; 

        UE_LOG(LogTemp, Warning, TEXT("Level Up! New Level: %d | Next Level XP: %d | Current XP : %d"), PlayerLevel, XPToNextLevel, CurrentXP);

        Health += 20;
        Damage += 5;  
    }
}

int APlayerZDChar::GetPlyHealth() const
{
    return Health;
}

int APlayerZDChar::GetPlyShield() const
{
    return Shield;
}

void APlayerZDChar::IncreaseShield(float Amount)
{
    Shield += Amount;
}

void APlayerZDChar::IncreaseAttack(float Amount)
{
    Damage += Amount;
}

void APlayerZDChar::BeginPlay()
{
	Super::BeginPlay();

	AnimationComponent = Cast<UPaperZDAnimationComponent>(GetComponentByClass(UPaperZDAnimationComponent::StaticClass()));

	PlyRotation = FPlayerDirection::Down;
}

void APlayerZDChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerZDChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveRight", this, &APlayerZDChar::MoveRight);
	InputComponent->BindAxis("MoveForeward", this, &APlayerZDChar::MoveForeward);
	InputComponent->BindAction("Attack", IE_Pressed, this, &APlayerZDChar::Attack);
    InputComponent->BindAction("Interact", IE_Pressed, this, &APlayerZDChar::Interact);
}

FRotator APlayerZDChar::GetRotation()
{
    switch (PlyRotation)
    {
    case FPlayerDirection::Up:
        return FRotator(0.f, 0.f, 0.f);
        break;
    case FPlayerDirection::Down:
        return FRotator(180.f, 0.f, 0.f);
        break;
    case FPlayerDirection::Left:
        return FRotator(0.f, -90.f, 0.f);
        break;
    case FPlayerDirection::Right:
        return FRotator(0.f, 90.f, 0.f);
        break;
    default:
        return FRotator(180.f, 0.f, 0.f);
        break;
    }
}

void APlayerZDChar::MoveForeward(float AxisValue)
{
    if (AxisValue != 0)
    {
        FVector Dir = FVector(1.f, 0.f, 0.f);
        AddMovementInput(Dir, AxisValue);
        if (AxisValue > 0)
        {
            PlyRotation = FPlayerDirection::Up;
        }
        else
        {
            PlyRotation = FPlayerDirection::Down;
        }
    }
}

void APlayerZDChar::MoveRight(float AxisValue)
{
    if (AxisValue != 0)
    {

        FVector Dir = FVector(0.f, 1.f, 0.f);
        AddMovementInput(Dir, AxisValue);
        if (AxisValue > 0)
        {
            PlyRotation = FPlayerDirection::Right;
        }
        else
        {
            PlyRotation = FPlayerDirection::Left;
        }
    }
}

void APlayerZDChar::Attack()
{
    APlayerController* PlayerController = Cast<APlayerController>(GetController());
    if (PlayerController)
    {
        isAttacking = true;
        FVector Location = GetActorLocation();
        FRotator Rotation = GetActorRotation();

        FVector Start = Location;
        FVector End = Start + (GetRotation().Vector() * 300.0f);

        FHitResult HitResult;

        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(this);

        bool bHit = GetWorld()->LineTraceSingleByChannel(
            HitResult,
            Start,
            End,
            ECC_GameTraceChannel1,//Custom enemy trace channel
            CollisionParams
        );

        if (bHit)
        {
            if (AEnemy* Enemy = Cast<AEnemy>(HitResult.GetActor()))
            {
                Enemy->ApplyDamage(Damage);

                UE_LOG(LogTemp, Warning, TEXT("Enemy: %s | Health: %d"), *Enemy->GetName(), Enemy->GetHealth());
            }        
        }

        // Debug line to visualize the trace
        DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1, 0, 1);
    }
}

void APlayerZDChar::MovePlayer(FVector Direction)
{
    FVector NewLocation = GetActorLocation() + Direction;
    SetActorLocation(NewLocation);

    UE_LOG(LogTemp, Warning, TEXT("Player moved to: %s"), *NewLocation.ToString());
}

void APlayerZDChar::ApplyDamage(int DamageAmount)
{
    Health -= DamageAmount;

    // Check if health has dropped to zero or below
    if (Health <= 0)
    {
        Health = 0;
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

        // Call the QuitGame function
        UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
    }

    UE_LOG(LogTemp, Log, TEXT("%d"), Health);
}

void APlayerZDChar::Interact()
{
    if (bCanInteract && InteractableActor)
    {
        if (AHealthFountain* Fountain = Cast<AHealthFountain>(InteractableActor))
        {
            Fountain->HealPlayer(this);
            Fountain->ChangeFlipbook();
        }
        else if (AChest* Chest = Cast<AChest>(InteractableActor))
        {
            Chest->ChangeFlipbook();
            Chest->GiveItemToPlayer(this);
        }
        else if (AMimic* Mimic = Cast<AMimic>(InteractableActor))
        {
            Mimic->TransformToEnemy();
        }
        else if (ADoor* Door = Cast<ADoor>(InteractableActor))
        {
            ARoom* CurrentRoom = GetCurrentRoom(); // Funzione che restituisce la stanza attuale del giocatore
            ARoom* NextRoom = Door->GetLinkedRoom(); // Stanza collegata dalla porta

            if (CurrentRoom && NextRoom)
            {
                // Determina la direzione in base alla porta
                FVector Direction;
                if (Door == CurrentRoom->NorthDoor)
                {
                    Direction = FVector(1500.0f, 0, 0); // Spostamento verso nord
                }
                else if (Door == CurrentRoom->SouthDoor)
                {
                    Direction = FVector(-1500.0f, 0, 0); // Spostamento verso sud
                }
                else if (Door == CurrentRoom->EastDoor)
                {
                    Direction = FVector(0, 1500.0f, 0); // Spostamento verso est
                }
                else if (Door == CurrentRoom->WestDoor)
                {
                    Direction = FVector(0, -1500.0f, 0); // Spostamento verso ovest
                }

                // Sposta il giocatore
                MovePlayer(Direction);

                // Trova il LevelManager e aggiorna la stanza
                TArray<AActor*> FoundActors;
                UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("LM"), FoundActors);

                for (AActor* Actor : FoundActors)
                {
                    ALevelManager* LevelManager = Cast<ALevelManager>(Actor);
                    if (LevelManager)
                    {
                        //// Disattiva la stanza corrente
                        //LevelManager->DeactivateAllRooms();

                        //// Attiva la nuova stanza
                        //LevelManager->ActivateRoomAt(NextRoom->GetRoomX(), NextRoom->GetRoomY());
                    }
                }
            }
        }
    }
}

void APlayerZDChar::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    if (OtherActor && (OtherActor->IsA(AHealthFountain::StaticClass()) ||
        OtherActor->IsA(AChest::StaticClass()) ||
        OtherActor->IsA(AMimic::StaticClass())) || 
        OtherActor->IsA(ADoor::StaticClass()))
    {
        bCanInteract = true;
        InteractableActor = OtherActor;
        UE_LOG(LogTemp, Warning, TEXT("Interazione possibile con: %s"), *OtherActor->GetName());
    }
}

void APlayerZDChar::NotifyActorEndOverlap(AActor* OtherActor)
{
    Super::NotifyActorEndOverlap(OtherActor);

    if (OtherActor && OtherActor == InteractableActor)
    {
        bCanInteract = false;
        InteractableActor = nullptr;
        UE_LOG(LogTemp, Log, TEXT("Interazione terminata con: %s"), *OtherActor->GetName());
    }
}

void APlayerZDChar::ReciveItem(AItem* Item)
{
    if (Item)
    {
        UE_LOG(LogTemp, Log, TEXT("Ricevuto oggetto: %s"), *Item->GetItemName());

        Item->Destroy();
    }
}

ARoom* APlayerZDChar::GetCurrentRoom() const
{
    // Retrieve the player's current location
    FVector PlayerLocation = GetActorLocation();

    // Calculate room coordinates from the player's location
    int32 PlayerX = FMath::RoundToInt(PlayerLocation.X / 1500.0f);
    int32 PlayerY = FMath::RoundToInt(PlayerLocation.Y / 1500.0f);

    // Find the LevelManager instance in the world
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("LM"), FoundActors);

    for (AActor* Actor : FoundActors)
    {
        ALevelManager* LevelManager = Cast<ALevelManager>(Actor);
        if (LevelManager)
        {
            // Return the room at the computed coordinates
            return LevelManager->GetRoomAt(PlayerX, PlayerY);
        }
    }

    // Return nullptr if no room is found
    return nullptr;
}
