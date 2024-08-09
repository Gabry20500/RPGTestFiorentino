// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerZDChar.h"
#include "PaperZDAnimationComponent.h"
#include "PaperZDAnimInstance.h"
#include <Enemy/Enemy.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Interactable/HealthFountain.h>
#include <Interactable/Chest.h>
#include <Interactable/Mimic.h>

APlayerZDChar::APlayerZDChar()
{
	PrimaryActorTick.bCanEverTick = true;

    Damage = 35;
    Health = 100;
    Shield = 0;

    bCanInteract = false;
    InteractableActor = nullptr;

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
            }        
        }

        // Debug line to visualize the trace
        DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1, 0, 1);
    }
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
    }
}

void APlayerZDChar::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    if (OtherActor && (OtherActor->IsA(AHealthFountain::StaticClass()) ||
        OtherActor->IsA(AChest::StaticClass()) ||
        OtherActor->IsA(AMimic::StaticClass())))
    {
        bCanInteract = true;
        InteractableActor = OtherActor;
        UE_LOG(LogTemp, Log, TEXT("Interazione possibile con: %s"), *OtherActor->GetName());
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
