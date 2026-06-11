#pragma once

#include "CoreMinimal.h"
#include "NetBaseCharacter.h"
#include "NetAvatar.generated.h"

UCLASS()
class ANetAvatar : public ANetBaseCharacter
{
    GENERATED_BODY()
public:
    ANetAvatar();
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void MoveForward(float Value);
    void MoveRight(float Value);
};