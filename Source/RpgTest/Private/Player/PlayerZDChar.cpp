// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerZDChar.h"
#include "PaperZDAnimationComponent.h"
#include "PaperZDAnimInstance.h"

APlayerZDChar::APlayerZDChar()
{
	PrimaryActorTick.bCanEverTick = true;
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

	// Log l'enum usando UE_LOG
	UE_LOG(LogTemp, Log, TEXT("Enum value: %s"), *UEnum::GetValueAsString(PlyRotation));
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

        // Ottieni l'istanza di animazione attuale
        UPaperZDAnimInstance* MyAnimInstance = AnimationComponent->GetAnimInstance();
        if (!MyAnimInstance)  UE_LOG(LogTemp, Warning, TEXT("No AnimInstance"));

        // Specifica il nome del nodo a cui vuoi saltare
        FName NodeName = "J_Attack";

        // Usa il metodo JumpToNode per saltare al nodo specificato
        MyAnimInstance->JumpToNode(NodeName);

        if (bHit)
        {
            AActor* HitActor = HitResult.GetActor();
            if (HitActor)
            {
                // Distruggi l'attore
                HitActor->Destroy();
            }        
        }

        // Debug line to visualize the trace
        DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1, 0, 1);
    }

    isAttacking = false;
}
