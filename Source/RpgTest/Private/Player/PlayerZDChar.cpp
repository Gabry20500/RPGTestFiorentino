// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerZDChar.h"
#include "PaperZDAnimationComponent.h"
#include "PaperZDAnimInstance.h"
#include <Enemy/Enemy.h>
#include <Kismet/KismetSystemLibrary.h>

APlayerZDChar::APlayerZDChar()
{
	PrimaryActorTick.bCanEverTick = true;

    Damage = 35;
    Health = 100;
    Shield = 0;
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
