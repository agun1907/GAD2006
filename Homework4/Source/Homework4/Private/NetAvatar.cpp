#include "NetAvatar.h"
#include "Components/InputComponent.h"

ANetAvatar::ANetAvatar()
{
}

void ANetAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &ANetAvatar::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ANetAvatar::MoveRight);
}

void ANetAvatar::MoveForward(float Value)
{
    if (Value != 0.0f) AddMovementInput(GetActorForwardVector(), Value);
}

void ANetAvatar::MoveRight(float Value)
{
    if (Value != 0.0f) AddMovementInput(GetActorRightVector(), Value);
}