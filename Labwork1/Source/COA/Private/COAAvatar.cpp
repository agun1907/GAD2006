#include "COAAvatar.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ACOAAvatar::ACOAAvatar()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->TargetArmLength = 300.0f;
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->bUsePawnControlRotation = true;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    Camera->bUsePawnControlRotation = false;

    bUseControllerRotationYaw = false;

    MaxStamina = 100.0f;
    Stamina = MaxStamina;
    StaminaDrainRate = 20.0f;
    StaminaGainRate = 15.0f;
    RunSpeed = 600.0f;
    bStaminaDrained = false;
    bRunning = false;
}

void ACOAAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);

    PlayerInputComponent->BindAxis("MoveForward", this, &ACOAAvatar::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ACOAAvatar::MoveRight);

    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ACOAAvatar::RunPressed);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &ACOAAvatar::RunReleased);
}

void ACOAAvatar::MoveForward(float value)
{
    if ((Controller != nullptr) && (value != 0.0f))
    {
        FRotator Rotation = GetController()->GetControlRotation();
        FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
        FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(ForwardDirection, value);
    }
}

void ACOAAvatar::MoveRight(float value)
{
    if ((Controller != nullptr) && (value != 0.0f))
    {
        FRotator Rotation = GetController()->GetControlRotation();
        FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
        FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(RightDirection, value);
    }
}

void ACOAAvatar::RunPressed()
{
    bRunning = true;
    UpdateMovementParams();
}

void ACOAAvatar::RunReleased()
{
    bRunning = false;
    UpdateMovementParams();
}

void ACOAAvatar::UpdateMovementParams()
{
    if (GetCharacterMovement())
    {
        if (bStaminaDrained)
        {
            GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
        }
        else if (bRunning)
        {
            GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
        }
        else
        {
            GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
        }
    }
}

void ACOAAvatar::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    bool bIsWalkingState = (GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Walking);
    bool bIsMoving = bIsWalkingState && (GetVelocity().SizeSquared() > 0.0f);

    if (bIsMoving && bRunning && !bStaminaDrained)
    {
        Stamina -= StaminaDrainRate * DeltaTime;

        if (Stamina <= 0.0f)
        {
            Stamina = 0.0f;
            bStaminaDrained = true;
            UpdateMovementParams();
        }
    }
    else
    {
        Stamina += StaminaGainRate * DeltaTime;

        if (Stamina >= MaxStamina)
        {
            Stamina = MaxStamina;

            if (bStaminaDrained)
            {
                bStaminaDrained = false;
                UpdateMovementParams();
            }
        }
    }
}