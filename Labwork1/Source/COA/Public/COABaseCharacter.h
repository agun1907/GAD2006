// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "COABaseCharacter.generated.h"

UCLASS()
class COA_API ACOABaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:

    ACOABaseCharacter();

protected:
 
    virtual void BeginPlay() override;

 
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COA")
    bool bDead;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "COA")
    float Health;

    UPROPERTY(EditAnywhere, Category = "COA")
    float MaxHealth;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "COA")
    float HealingRate;

    UPROPERTY(EditAnywhere, Category = "COA")
    float WalkSpeed;

public:

    virtual void Tick(float DeltaTime) override;
};