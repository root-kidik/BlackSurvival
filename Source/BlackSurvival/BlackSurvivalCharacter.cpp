// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlackSurvivalCharacter.h"

#include "BS_InteractableActor.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "Logging/StructuredLog.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ABlackSurvivalCharacter::ABlackSurvivalCharacter()
{
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw   = false;
    bUseControllerRotationRoll  = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate              = FRotator(0.0f, 500.0f, 0.0f);

    GetCharacterMovement()->JumpZVelocity              = 700.f;
    GetCharacterMovement()->AirControl                 = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed               = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed         = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
    GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength         = 700.0f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    InteractCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("InteractCapsuleComponent"));
    InteractCapsuleComponent->InitCapsuleSize(128.f, 128.f);
    InteractCapsuleComponent->SetupAttachment(RootComponent);
}

void ABlackSurvivalCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(JumpAction);
    check(MoveAction);
    check(LookAction);
    check(InteractAction);
}

void ABlackSurvivalCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
                PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {

        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABlackSurvivalCharacter::Move);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABlackSurvivalCharacter::Look);
        EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ABlackSurvivalCharacter::Interact);
    }
    else
    {
        UE_LOG(LogTemplateCharacter,
               Error,
               TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input "
                    "system. If you intend to use the legacy system, then you will need to update this C++ file."),
               *GetNameSafe(this));
    }
}

void ABlackSurvivalCharacter::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection   = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(ForwardDirection, MovementVector.Y);
        AddMovementInput(RightDirection, MovementVector.X);
    }
}

void ABlackSurvivalCharacter::Look(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

void ABlackSurvivalCharacter::Interact(const FInputActionValue& Value)
{
    TArray<AActor*> InteractableActors;
    InteractCapsuleComponent->GetOverlappingActors(InteractableActors, ABS_InteractableActor::StaticClass());

    if (InteractableActors.IsEmpty())
    {
        return;
    }

    auto* FirstInteractableActor = Cast<ABS_InteractableActor>(InteractableActors.Top());
    FirstInteractableActor->Interact();
}