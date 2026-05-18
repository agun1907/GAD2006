#pragma once

#include "CoreMinimal.h"
#include "COABaseCharacter.h"
#include "COAAvatar.generated.h"

UCLASS()
class COA_API ACOAAvatar : public ACOABaseCharacter
{
    GENERATED_BODY()

public:
    ACOAAvatar();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
    class UCameraComponent* Camera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
    class USpringArmComponent* SpringArm;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
    float Stamina;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
    float MaxStamina;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
    float StaminaGainRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
    float StaminaDrainRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
    float RunSpeed;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COA")
    bool bStaminaDrained;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COA")
    bool bRunning;

    void UpdateMovementParams();
    void RunPressed();
    void RunReleased();

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void Tick(float DeltaTime) override;

private:
    void MoveForward(float value);
    void MoveRight(float value);
};