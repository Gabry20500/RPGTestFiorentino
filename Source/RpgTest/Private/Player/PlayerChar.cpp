// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerChar.h"

APlayerChar::APlayerChar()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerChar::BeginPlay()
{
	Super::BeginPlay();

    Body = Cast<UStaticMeshComponent>(GetComponentByClass(UStaticMeshComponent::StaticClass()));

    inMovement = false;
    PlyRotation = FPlayerDirection::Down;
}

void APlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // Log l'enum usando UE_LOG
    UE_LOG(LogTemp, Log, TEXT("Enum value: %s"), *UEnum::GetValueAsString(PlyRotation));
}

void APlayerChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveRight", this, &APlayerChar::MoveRight);
	InputComponent->BindAxis("MoveForeward", this, &APlayerChar::MoveForeward);
    InputComponent->BindAction("Attack", IE_Pressed, this, &APlayerChar::Attack);
}

void APlayerChar::MoveForeward(float AxisValue)
{
    if (AxisValue != 0) 
    {
        inMovement = true;
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
    else
    {
        inMovement = false;
    }
}


void APlayerChar::MoveRight(float AxisValue)
{
    if (AxisValue != 0)
    {
        inMovement = true;
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
    else
    {
        inMovement = false;
    }
}

void APlayerChar::Attack()
{
    APlayerController* PlayerController = Cast<APlayerController>(GetController());
    if (PlayerController)
    {
        FVector Location = GetActorLocation();
        FRotator Rotation = GetActorRotation();

        FVector Start = Location;
        FVector End = Start + (Rotation.Vector() * 300.0f);

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
            UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *HitResult.GetActor()->GetName());
        }

        // Debug line to visualize the trace
        DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1, 0, 1);
    }
}
