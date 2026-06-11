#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NetGameMode.generated.h"

UCLASS()
class ANetGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ANetGameMode();
    virtual void BeginPlay() override;
    virtual void PostLogin(APlayerController* NewPlayer) override;


    FTimerHandle BlueTeamWinTimer;

    UFUNCTION()
    void OnBlueTeamTimeout();
};