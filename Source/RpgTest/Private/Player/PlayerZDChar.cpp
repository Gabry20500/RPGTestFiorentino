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
#include "Item/AttackPotion.h"
#include "Item/ShieldPotion.h"
#include "Blueprint/UserWidget.h"
#include "Minimap/Minimap.h"
#include <Kismet/GameplayStatics.h>


APlayerZDChar::APlayerZDChar()
{
	PrimaryActorTick.bCanEverTick = true;

    Damage = 35;
    Health = 100;
    Shield = 0;

    bCanInteract = false;
    InteractableActor = nullptr;
    bIsMinimapVisible = false;

    PlayerLevel = 1;
    CurrentXP = 0;
    XPToNextLevel = 100;

    AttackPotionCount = 0;
    ShieldPotionCount = 0;
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

void APlayerZDChar::ApplyState(EPlayerState NewState, float StateDuration)
{
    CurrentState = NewState;

    UpdatePlayerColor();

    switch (CurrentState)
    {
    case EPlayerState::Poisoned:
        PoisonDuration = StateDuration;
        GetWorldTimerManager().SetTimer(StateTimerHandle, this, &APlayerZDChar::PoisonTick, 1.0f, true);
        break;
    case EPlayerState::Burning:
        BurningDuration = StateDuration;
        GetWorldTimerManager().SetTimer(StateTimerHandle, this, &APlayerZDChar::BurnTick, 1.0f, true);
        break;
    default:
        break;
    }
}

void APlayerZDChar::ManageMinimap()
{
    if (bIsMinimapVisible == false)
    {
        if (ALevelManager* LevelManager = GetLevelManager())
        {
            LevelManager->ToggleMinimap(true);
            bIsMinimapVisible = true;
        }
    }
    else
    {
        if (ALevelManager* LevelManager = GetLevelManager())
        {
            LevelManager->ToggleMinimap(false);
            bIsMinimapVisible = false;
        }
    }
}

void APlayerZDChar::HideMinimap()
{
    if (ALevelManager* LevelManager = GetLevelManager())
    {
        LevelManager->ToggleMinimap(false);
    }
}

void APlayerZDChar::BeginPlay()
{
	Super::BeginPlay();

	AnimationComponent = Cast<UPaperZDAnimationComponent>(GetComponentByClass(UPaperZDAnimationComponent::StaticClass()));
    PlayerFlipbook = FindComponentByClass<UPaperFlipbookComponent>();

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

    InputComponent->BindAction("UseShieldPotion", IE_Pressed, this, &APlayerZDChar::UseShieldPotion);
    InputComponent->BindAction("UseAttackPotion", IE_Pressed, this, &APlayerZDChar::UseAttackPotion);

    InputComponent->BindAction("ToggleMinimap", IE_Pressed, this, &APlayerZDChar::ManageMinimap);

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

    // Trova il LevelManager
    ALevelManager* LevelManager = GetLevelManager();
    if (LevelManager)
    {
        // Convert NewLocation to grid coordinates (assuming each grid cell is 1500 units in size)
        int32 NewX = FMath::RoundToInt(NewLocation.X / 1500.0f);
        int32 NewY = FMath::RoundToInt(NewLocation.Y / 1500.0f);

        LevelManager->MovePlayer(NewX, NewY);
    }

    UE_LOG(LogTemp, Warning, TEXT("Player moved to: %s"), *NewLocation.ToString());
}

ALevelManager* APlayerZDChar::GetLevelManager() const
{
    return Cast<ALevelManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ALevelManager::StaticClass()));
}

void APlayerZDChar::UpdatePlayerColor()
{
    switch (CurrentState)
    {
    case EPlayerState::Poisoned:
        PlayerFlipbook->SetSpriteColor(FLinearColor::Green);
        break;
    case EPlayerState::Burning:
        PlayerFlipbook->SetSpriteColor(FLinearColor::Red);
        break;
    case EPlayerState::Normal:
    default:
        PlayerFlipbook->SetSpriteColor(FLinearColor::White);
        break;
    }
}

void APlayerZDChar::PoisonTick()
{
    ApplyDamage(5);  // Danno da veleno ogni secondo
    PoisonDuration -= 1.0f;

    if (PoisonDuration <= 0.0f)
    {
        // Rimuove lo stato di avvelenamento
        ClearState();
    }
}

void APlayerZDChar::BurnTick()
{
    ApplyDamage(10);  // Danno da bruciore ogni secondo
    BurningDuration -= 1.0f;

    if (BurningDuration <= 0.0f)
    {
        // Rimuove lo stato di bruciore
        ClearState();
    }
}

void APlayerZDChar::ClearState()
{
    GetWorldTimerManager().ClearTimer(StateTimerHandle);
    CurrentState = EPlayerState::Normal;
    UpdatePlayerColor();
}



void APlayerZDChar::UseShieldPotion()
{
    if (ShieldPotionCount > 0)
    {
        IncreaseShield(50.0f);
        ShieldPotionCount--;
        UE_LOG(LogTemp, Log, TEXT("Usata pozione di scudo. Scudo attuale: %d | Pozioni rimaste: %d"), Shield, ShieldPotionCount);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Non hai pozioni di scudo!"));
    }
}

void APlayerZDChar::UseAttackPotion()
{
    if (AttackPotionCount > 0)
    {
        IncreaseAttack(10);
        AttackPotionCount--;
        UE_LOG(LogTemp, Log, TEXT("Pozione di attacco usata! Attacco attuale: %d | Pozioni d'attacco rimaste: %d"), Damage, AttackPotionCount);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Non ci sono pozioni di attacco!"));
    }
}

void APlayerZDChar::ApplyDamage(int DamageAmount)
{
    UE_LOG(LogTemp, Log, TEXT("Applying Damage: %d"), DamageAmount);

    // Se il giocatore ha scudo, intacca prima quello
    if (Shield > 0)
    {
        if (DamageAmount <= Shield)
        {
            // Il danno è inferiore o uguale allo scudo, quindi riduce solo lo scudo
            Shield -= DamageAmount;
            UE_LOG(LogTemp, Log, TEXT("Damage absorbed by shield. Remaining shield: %d"), Shield);
        }
        else
        {
            // Il danno eccede lo scudo, quindi intacca anche la salute
            int32 RemainingDamage = DamageAmount - Shield;
            Shield = 0; // Scudo esaurito
            UE_LOG(LogTemp, Log, TEXT("Shield depleted. Remaining damage to health: %d"), RemainingDamage);

            // Riduci la salute con il danno rimanente
            Health -= RemainingDamage;
        }
    }
    else
    {
        // Se non c'è scudo, applica tutto il danno alla salute
        Health -= DamageAmount;
    }

    // Log del valore della salute residua
    UE_LOG(LogTemp, Log, TEXT("Remaining health: %d"), Health);

    // Se la salute va a 0 o meno, considera il giocatore morto
    if (Health <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player is dead!"));
        // Qui puoi implementare la logica per la morte del personaggio, come ad esempio giocare un'animazione, cambiare stato, etc.

    };
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
                    Direction = FVector(300.0f, 0, 0); // Spostamento verso nord
                }
                else if (Door == CurrentRoom->SouthDoor)
                {
                    Direction = FVector(-300.0f, 0, 0); // Spostamento verso sud
                }
                else if (Door == CurrentRoom->EastDoor)
                {
                    Direction = FVector(0, 300.0f, 0); // Spostamento verso est
                }
                else if (Door == CurrentRoom->WestDoor)
                {
                    Direction = FVector(0, -300.0f, 0); // Spostamento verso ovest
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
        UE_LOG(LogTemp, Log, TEXT("Received Item: %s"), *Item->GetClass()->GetName());

        if (Item->IsA(AAttackPotion::StaticClass()))
        {
            AttackPotionCount++;
            UE_LOG(LogTemp, Log, TEXT("Received a Attack Potion. Total: %d"), AttackPotionCount);
        }
        else if (Item->IsA(AShieldPotion::StaticClass()))
        {
            ShieldPotionCount++;
            UE_LOG(LogTemp, Log, TEXT("Received a Shield Potion. Total: %d"), ShieldPotionCount);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Received an item of unknown type."));
        }

        // Distruggi l'oggetto dopo che è stato ricevuto
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
